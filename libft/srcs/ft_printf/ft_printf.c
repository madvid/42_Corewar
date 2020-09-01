/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 11:28:15 by yaye              #+#    #+#             */
/*   Updated: 2020/09/01 17:30:01 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ft_printf.h"
#include "libft.h"

void	new_arg(t_pfarg *new)
{
	new->flg.hsh = 0;
	new->flg.spc = 0;
	new->flg.pls = 0;
	new->flg.zro = 0;
	new->flg.neg = 0;
	new->fld = 0;
	new->prc = -2;
	new->mod = 0;
	new->typ = 0;
	new->len = 0;
	new->extra = 0;
	new->fill = 0;
	new->i = 0;
}

void	fill_buf(t_pf *env, char c)
{
	if (env->i >= PF_BUF)
	{
		write(1, &env->str[0], PF_BUF);
		ft_bzero(env->str, PF_BUF);
		env->i = 0;
	}
	env->str[env->i++] = c;
	env->len = env->len + 1;
}

void	to_bi(long double f, char *s)
{
	char	*p;
	int		i;
	int		j;
	int		k;

	k = 0;
	p = (char *)&f;
	j = -1;
	while (++j < 10)
	{
		i = -1;
		while (++i < 8)
			s[k++] = (*p >> i & 1) ? '1' : '0';
		p = p + 1;
	}
	s[k] = 0;
}

int		naninf(long double n, char *s, t_pfarg *arg)
{
	to_bi(n, arg->f);
	to_bi(1. / 0, arg->inf);
	to_bi(0. / 0, arg->nan);
	if (!ft_strncmp(arg->f, arg->inf, 80))
	{
		s[arg->i++] = 'i';
		s[arg->i++] = 'n';
		s[arg->i++] = 'f';
		arg->len = arg->len + 3;
		arg->flg.zro = 0;
		return (1);
	}
	else if (!ft_strncmp(arg->f, arg->nan, 80))
	{
		s[arg->i++] = 'n';
		s[arg->i++] = 'a';
		s[arg->i++] = 'n';
		arg->len = arg->len + 3;
		arg->extra = 0;
		arg->flg.zro = 0;
		return (-1);
	}
	return (0);
}

int		ft_printf(const char *str, ...)
{
	t_pf	env;
	int		i;

	if (!str)
		return (0);
	va_start(env.vali, str);
	env.i = 0;
	env.len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
			i = i + parse(str + i, &env);
		else
			fill_buf(&env, str[i++]);
	}
	write(1, env.str, env.i);
	va_end(env.vali);
	return (env.len);
}
