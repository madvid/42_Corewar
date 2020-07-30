/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 10:34:07 by yaye              #+#    #+#             */
/*   Updated: 2020/07/17 10:34:09 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

size_t	is_hname(t_asm *a, char *s)
{
	size_t	t;
	int		i;
	size_t	len;

	t = 0;
	if (!ft_strnequ(s, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		return (0);
	if (a->name++ == 1)
		leave(a, ": MULTIPLE NAME_CMD_STRING COMMAND.\n", t);
	t = ft_strlen(NAME_CMD_STRING);
	while (s[t] == ' ' || s[t] == '\t' || s[t] == '\v')
		t += 1;
	if (s[t++] != '"')
		leave(a, ": SYNTAX ERROR AT TOKEN COMMAND NAME_CMD_STRING.\n", t);
	i = 4;
	len = t;
	while (s[t] && t <= (len + PROG_NAME_LENGTH)\
		&& s[t] != '"')
		asto_bi(a, &i, s[t++], 1);
	a->size -= t - len;
	if (t > (len + PROG_NAME_LENGTH))
		leave(a, ": PROG_NAME_LENGTH EXCEEDED.\n", t);
	if (s[t++] != '"')
		leave(a, ": SYNTAX ERROR AT TOKEN COMMAND NAME_CMD_STRING.\n", t);
	return (t += is_endline(a, s + t));
}

size_t	is_hcomment(t_asm *a, char *s)
{
	size_t	t;
	int		i;
	size_t	len;

	t = 0;
	if (!ft_strnequ(s, COMMENT_CMD_STRING, 8))
		return (0);
	if (a->comm++ == 1)
		leave(a, ": MULTIPLE COMMENT_CMD_STRING COMMAND.\n", t);
	t = ft_strlen(COMMENT_CMD_STRING);
	while (s[t] == ' ' || s[t] == '\t' || s[t] == '\v')
		t += 1;
	if (s[t++] != '"')
		leave(a, ": SYNTAX ERROR AT TOKEN COMMAND COMMENT_CMD_STRING.\n", t);
	i = (PROG_NAME_LENGTH + 12);
	len = t;
	while (s[t] && t <= (len + COMMENT_LENGTH) \
		&& s[t] != '"')
		asto_bi(a, &i, s[t++], 1);
	a->size -= t - len;
	if (t > (len + COMMENT_LENGTH))
		leave(a, ": COMMENT_LENGTH EXCEEDED.\n", t);
	if (s[t++] != '"')
		leave(a, ": SYNTAX ERROR AT TOKEN COMMAND COMMENT_CMD_STRING.\n", t);
	return (t += is_endline(a, s + t));
}

size_t	is_op(t_asm *a, char *s)
{
	size_t	t;
	size_t	i;

	t = 0;
	while (s[t] >= 'a' && s[t] <= 'z')
		t += 1;
	i = 0;
	while (i < 16)
	{
		if (ft_strnequ(s, a->op_tab[i].name, t))
			return (i);
		i += 1;
	}
	ft_printf("%s\n", s);
	leave(a, ": SYNTAX ERROR IN INSTRUCTION LINE.\n", t);
	return (16);
}

void	get_labeldef(t_asm *a, char *s, size_t len)
{
	t_lb		*l;
	t_lb		*tmp;

	if (!(l = malloc(sizeof(t_lb))))
		leave(a, ": failed to malloc in get_labeldef().\n", 0);
	if (!(l->lb = malloc(sizeof(char) * len + 1)))
		leave(a, ": failed to malloc in get_labeldef().\n", 0);
	ft_strncpy(l->lb, s, len);
	l->lb[len] = 0;
	l->i_op = a->i;
	l->next = NULL;
	if (a->ldef == NULL)
		a->ldef = l;
	else
	{
		tmp = a->ldef;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = l;
	}
}

size_t	get_labelcall(t_asm *a, char *s, size_t byte_size, t_ope *ope)
{
	size_t		t;
	t_lb		*l;
	t_lb		*tmp;

	t = 0;
	while (ft_strchr(LABEL_CHARS, s[t]))
		t += 1;
	if (!(l = malloc(sizeof(t_lb))) \
		|| !(l->lb = malloc(sizeof(char) * t + 1)) || !ft_strncpy(l->lb, s, t))
		leave(a, ": failed to malloc in get_labelcall().\n", 0);
	l->lb[t] = 0;
	l->i_op = ope->i_op;
	l->i_call = a->i;
	l->byte_size = byte_size;
	l->next = NULL;
	if ((l->line = a->line) >= 0 && a->lcall == NULL)
		a->lcall = l;
	else
	{
		tmp = a->lcall;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = l;
	}
	return (t);
}

size_t	asto_i(char *str, int *value)
{
	size_t	j;
	int		m;
	size_t	n;

	if (!str)
		return (0);
	j = 0;
	if (str[j] != '-' && !ft_isdigit(str[j]))
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

size_t	get_arg(t_asm *a, char *s, size_t op, t_ope *ope)
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
		else if ((s[t] == DIRECT_CHAR \
			&& (a->op_tab[op].type[ope->n_arg] & T_DIR)) \
			|| ((s[t] == LABEL_CHAR || ft_isdigit(s[t]) || s[t] == '-') \
				&& (a->op_tab[op].type[ope->n_arg] & T_IND)))
			t += get_else(a, s + t, op, ope);
		else
			leave(a, ": SYNTAX ERROR INVALID ARGUMENT.\n", t);
		ope->n_arg += 1;
		while (s[t] == ' ' || s[t] == '\t' || s[t] == '\v')
			t += 1;
		if (s[t] != SEPARATOR_CHAR && ope->n_arg < a->op_tab[op].n_arg)
			leave(a, ": SYNTAX ERROR MISSING SEPARATOR_CHAR.\n", t);
		else if (s[t] == SEPARATOR_CHAR && (t += 1) > 0 \
			&& ope->n_arg == a->op_tab[op].n_arg)
			leave(a, ": SYNTAX ERROR EXCEEDING MAX N_ARGUMENT.\n", t);
	}
	return (t);
}

size_t	get_arguments(t_asm *a, char *s, size_t op)
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
	t = get_arg(a, s, op, &ope);
	if (a->op_tab[op].encod)
		asto_bi(a, &ope.i_encod, ope.encoded, 1);
	return (t += is_endline(a, s + t));
}

size_t	is_opline(t_asm *a, char *s)
{
	size_t	t;
	size_t	op;

	t = 0;
	while (ft_strchr(LABEL_CHARS, s[t]))
		t++;
	if (!t)
		return (0);
	if (a->name != 1 || a->comm != 1)
		leave(a, ": MISSING NAME_CMD_STRING AND/OR COMMENT_CMD_STRING.\n", t);
	if (s[t] == ':')
	{
		get_labeldef(a, s, t++);
		return (t += is_endline(NULL, s + t));
	}
	if ((op = is_op(a, s)) == 16)
		leave(a, ": SYNTAX ERROR INVALID OPERATION.\n", t);
	return (t += get_arguments(a, s + t, op));
}

void	get_cor(t_asm *a)
{
	size_t	i;
	size_t	t;

	a->size = 0;
	i = 0;
	while (a->chp[i])
	{
		while (a->chp[i] == ' ' || a->chp[i] == '\t' || a->chp[i] == '\v')
			i += 1;
		if ((t = is_hname(a, a->chp + i)) > 0)
			i += t;
		else if ((t = is_hcomment(a, a->chp + i)) > 0)
			i += t;
		else if ((t = is_opline(a, a->chp + i)) > 0)
			i += t;
		else if ((t = is_endline(a, a->chp + i)) > 0)
			i += t;
		else
			leave(a, ": SYNTAX ERROR INVALID LINE.\n", 0);
	}
	if (a->chp[i] == 0 && i > 1 && a->chp[i - 1] != '\n')
		leave(a, ": NO EMPTY LINE AT END OF FILE.\n", 0);
}
