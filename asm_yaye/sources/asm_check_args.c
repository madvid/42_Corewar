/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 13:29:08 by yaye              #+#    #+#             */
/*   Updated: 2020/07/31 13:29:12 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

size_t	asto_i(char *str, int *value)
{
	size_t	j;
	int		m;
	size_t	n;

	if (!(j = 0) && str[j] != '-' && !ft_isdigit(str[j]))
		return (0);
	m = (str[j] == '-') ? -1 : 1;
	if (!(n = 0) && !ft_isdigit(str[j]) && !ft_isdigit(str[++j]))
		return (0);
	while (ft_isdigit(str[j]))
	{
		if ((n == 922337203685477580 && (str[j] - '0') < 8) \
			|| n < 922337203685477580)
			n = n * 10 + (str[j] - '0');
		else
		{
			n = (m > 0) ? 9223372036854775807 : 0;
			break ;
		}
		j = j + 1;
	}
	*value = m * n;
	while (ft_isdigit(str[j]))
		j = j + 1;
	return (j);
}

size_t	get_register(t_asm *a, char *s)
{
	size_t	t;
	int		value;

	t = 0;
	if (!ft_isdigit(s[t]))
		leave(a, ": SYNTAX ERROR INVALID REGISTER.\n", t);
	value = 0;
	value = value * 10 + (s[t++] - '0');
	if (ft_isdigit(s[t]))
		value = value * 10 + (s[t++] - '0');
	asto_bi(a, &a->i, value, 1);
	return (t);
}

size_t	get_else(t_asm *a, char *s, size_t op, t_ope *ope)
{
	size_t	t;
	int		value;
	int		size;

	t = 0;
	ope->encoded += ft_power(2, (ope->p_encod -= 2) + 2);
	if (s[0] != DIRECT_CHAR)
		ope->encoded += ft_power(2, ope->p_encod + 1);
	else
		t += 1;
	value = 0;
	size = (s[0] == DIRECT_CHAR) \
	? 4 - (a->op_tab[op].direct_size * 2) : 2;
	if (s[t] == LABEL_CHAR && (t += 1) > 0)
	{
		t += get_labelcall(a, s + t, size, ope);
		a->i += size;
	}
	else if (asto_i(s + t, &value) > 0)
		asto_bi(a, &a->i, value, size);
	else
		leave(a, ": SYNTAX ERROR INVALID ARGUMENT.\n", t);
	return (t += asto_i(s + t, &value));
}

size_t	get_args(t_asm *a, char *s, size_t op, t_ope *ope)
{
	size_t	t;

	t = 0;
	while (s[t] && ope->n_arg < a->op_tab[op].n_arg)
	{
		while (s[t] == ' ' || s[t] == '\t' || s[t] == '\v')
			t += 1;
		if (s[t] == 'r' && (a->op_tab[op].type[ope->n_arg] & T_REG) \
			&& (ope->encoded += ft_power(2, (ope->p_encod -= 2) + 1)) > 0)
			t += get_register(a, s + t + 1) + 1;
		else if ((s[t] == DIRECT_CHAR && (a->op_tab[op].type[ope->n_arg] \
			& T_DIR)) || ((s[t] == LABEL_CHAR || ft_isdigit(s[t]) \
			|| s[t] == '-') && (a->op_tab[op].type[ope->n_arg] & T_IND)))
			t += get_else(a, s + t, op, ope);
		else
			leave(a, ": SYNTAX ERROR INVALID ARGUMENT.\n", t);
		ope->n_arg += 1;
		while (s[t] == ' ' || s[t] == '\t' || s[t] == '\v')
			t += 1;
		if ((s[t] != SEPARATOR_CHAR && ope->n_arg < a->op_tab[op].n_arg) || \
			(s[t] == SEPARATOR_CHAR && (t += 1) > 0 \
				&& ope->n_arg == a->op_tab[op].n_arg))
			leave(a, ": SYNTAX ERROR.\n", t);
	}
	return (t);
}

size_t	check_args(t_asm *a, char *s, size_t op)
{
	t_ope	ope;
	size_t	t;

	ope.i_op = a->i;
	asto_bi(a, &a->i, a->op_tab[op].code, 1);
	ope.i_encod = a->i;
	if (a->op_tab[op].encod)
		a->i += 1;
	ope.encoded = 0;
	ope.p_encod = 7;
	ope.n_arg = 0;
	t = get_args(a, s, op, &ope);
	if (a->op_tab[op].encod)
		asto_bi(a, &ope.i_encod, ope.encoded, 1);
	return (t += is_endline(a, s + t));
}
