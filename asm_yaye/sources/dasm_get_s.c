/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_get_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:55:00 by yaye              #+#    #+#             */
/*   Updated: 2020/08/07 13:55:01 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

void	addto_s(t_dasm *a, char *s, int n)
{
	static int	i = 0;
	int			j;

	j = 0;
	while (j < n)
	{
		a->chp[i] = s[j];
		i += 1;
		j += 1;
	}
	a->chp[i] = 0;
}

void	ito_s(t_dasm *a, int n)
{
	char	c;

	if (n < 0)
	{
		if (n == -2147483648)
		{
			addto_s(a, "-2147483648", 11);
			return ;
		}
		n = -n;
		addto_s(a, "-", 1);
	}
	if (n < 10)
	{
		c = n + '0';
		addto_s(a, &c, 1);
	}
	else
	{
		ito_s(a, n / 10);
		c = n % 10 + '0';
		addto_s(a, &c, 1);
	}
}

int		get_arg_value(t_dasm *a, t_op op_line, int type)
{
	int		value;

	if ((type == REG_CODE && a->i >= COR_MAX) \
		|| (type == IND_CODE && a->i + 2 > COR_MAX) \
		|| (type == DIR_CODE && a->i + 4 > COR_MAX))
		leave(a, ": MISSING ARGUMENT.\n");
	value = a->cor[++a->i];
	if (type == REG_CODE)
	{
		addto_s(a, "r", 1);
		return (value);
	}
	value = value << 8 | a->cor[++a->i];
	if (type == IND_CODE)
		return (value);
	if (type == DIR_CODE)
	{
		addto_s(a, "%", 1);
		if (op_line.direct_size == 1)
			return (value);
		value = value << 8 | a->cor[++a->i];
		return ((value = value << 8 | a->cor[++a->i]));
	}
	leave(a, NULL);
	return (0);
}

void	get_oparg(t_dasm *a, t_op op_line)
{
	int		enc_byte;
	size_t	nb_arg;
	int		mask;
	int		type;

	if (!op_line.encod)
		return (ito_s(a, get_arg_value(a, op_line, DIR_CODE)));
	enc_byte = a->cor[++a->i];
	nb_arg = 0;
	while (nb_arg < op_line.n_arg)
	{
		mask = ft_power(2, 7 - (2 * nb_arg)) + ft_power(2, 6 - (2 * nb_arg));
		type = (enc_byte & mask) >> (6 - (2 * nb_arg));
		if (type == REG_CODE && (op_line.type[nb_arg] & T_REG) != 0)
			ito_s(a, get_arg_value(a, op_line, REG_CODE));
		else if (type == IND_CODE && (op_line.type[nb_arg] & T_IND) != 0)
			ito_s(a, get_arg_value(a, op_line, IND_CODE));
		else if (type == DIR_CODE && (op_line.type[nb_arg] & T_DIR) != 0)
			ito_s(a, get_arg_value(a, op_line, DIR_CODE));
		if (nb_arg + 1 < op_line.n_arg)
			addto_s(a, ", ", 2);
		nb_arg += 1;
	}
}

void	get_s(t_dasm *a)
{
	a->i = 4;
	addto_s(a, ".name \"", 7);
	addto_s(a, a->cor + 4, ft_strlen(a->cor + 4));
	addto_s(a, "\"\n.comment \"", 12);
	addto_s(a, a->cor + (PROG_NAME_LENGTH + 12)\
		, ft_strlen(a->cor + (PROG_NAME_LENGTH + 12)));
	addto_s(a, "\"\n\n", 3);
	a->i = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	while (a->cor[a->i] > 0 && a->cor[a->i] <= 16)
	{
		addto_s(a, a->op_tab[a->cor[a->i] - 1].name\
			, ft_strlen(a->op_tab[a->cor[a->i] - 1].name));
		addto_s(a, " ", 1);
		get_oparg(a, a->op_tab[a->cor[a->i] - 1]);
		addto_s(a, "\n", 1);
		a->i += 1;
	}
}
