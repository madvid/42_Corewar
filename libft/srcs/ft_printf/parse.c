/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 11:28:48 by yaye              #+#    #+#             */
/*   Updated: 2020/09/01 17:30:33 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		isflag(char c, t_pfarg *arg)
{
	if (arg)
	{
		if (c == '#')
			arg->flg.hsh = 1;
		if (c == '0')
			arg->flg.zro = 1;
		if (c == '-')
			arg->flg.neg = 1;
		if (c == '+')
			arg->flg.pls = '+';
		if (c == ' ')
			arg->flg.spc = ' ';
		return (0);
	}
	if (c == '#')
		return (1);
	if (c == '0')
		return (2);
	if (c == '-')
		return (3);
	if (c == '+')
		return (4);
	if (c == ' ')
		return (5);
	return (0);
}

int		ismod(const char *str, int *i)
{
	if (*str == 'h' && *(str + 1) == 'h')
	{
		*i = *i + 1;
		return (1);
	}
	if (*str == 'h')
		return (2);
	if ((*str == 'l' && *(str + 1) == 'l') || *str == 'L')
	{
		*i = *i + 1;
		return (3);
	}
	if (*str == 'l')
		return (4);
	return (0);
}

int		istype(char c)
{
	if (c == '%')
		return (13);
	if (c == 'd' || c == 'i')
		return (1);
	if (c == 'o')
		return (3);
	if (c == 'u')
		return (4);
	if (c == 'x')
		return (5);
	if (c == 'X')
		return (6);
	if (c == 'c')
		return (7);
	if (c == 's')
		return (8);
	if (c == 'p')
		return (9);
	if (c == 'f')
		return (10);
	return ((c == 'b') ? 12 : 0);
}

void	procc(t_pf *env, t_pfarg *arg)
{
	if (arg->typ == 1)
		parse_di(env, arg);
	if (arg->typ == 3)
		parse_o(env, arg);
	if (arg->typ == 4)
		parse_u(env, arg);
	if (arg->typ == 5)
		parse_x(env, arg);
	if (arg->typ == 6)
		parse_xcap(env, arg);
	if (arg->typ == 7)
		parse_c(env, arg);
	if (arg->typ == 8)
		parse_s(env, arg);
	if (arg->typ == 9)
		parse_p(env, arg);
	if (arg->typ == 10)
		parse_f(env, arg);
	if (arg->typ == 12)
		parse_b(env, arg);
	if (arg->typ == 13)
		parse_percent(env, arg);
}

int		parse(const char *str, t_pf *env)
{
	t_pfarg	arg;
	int		i;

	new_arg(&arg);
	i = 1;
	while (isflag(str[i], NULL))
		isflag(str[i++], &arg);
	arg.flg.zro = (arg.flg.neg) ? 0 : arg.flg.zro;
	while (ft_isdigit(str[i]))
		arg.fld = arg.fld * 10 + str[i++] - '0';
	if (str[i] == '.')
	{
		i = i + 1;
		arg.prc = 0;
	}
	while (ft_isdigit(str[i]))
		arg.prc = arg.prc * 10 + str[i++] - '0';
	if ((arg.mod = ismod(str + i, &i)))
		i = i + 1;
	if ((arg.typ = istype(str[i])))
		i = i + 1;
	procc(env, &arg);
	return (i);
}
