/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:54:25 by yaye              #+#    #+#             */
/*   Updated: 2019/07/25 17:54:27 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

void	fill_null(t_pf *env, t_pfarg *arg)
{
	if (arg->len-- > 0)
		fill_buf(env, '(');
	if (arg->len-- > 0)
		fill_buf(env, 'n');
	if (arg->len-- > 0)
		fill_buf(env, 'u');
	if (arg->len-- > 0)
		fill_buf(env, 'l');
	if (arg->len-- > 0)
		fill_buf(env, 'l');
	if (arg->len-- > 0)
		fill_buf(env, ')');
}

void	fill_sneg(char *n, t_pf *env, t_pfarg *arg)
{
	int		i;

	if (arg->extra)
		fill_null(env, arg);
	else
	{
		i = -1;
		while (++i < arg->len)
			fill_buf(env, n[i]);
	}
	while (--arg->fill > 0)
		fill_buf(env, ' ');
}

void	fill_sels(char *n, t_pf *env, t_pfarg *arg)
{
	int		i;

	while (--arg->fill > 0)
		fill_buf(env, ' ');
	if (arg->extra)
		fill_null(env, arg);
	else
	{
		i = -1;
		while (++i < arg->len)
			fill_buf(env, n[i]);
	}
}

void	parse_s(t_pf *env, t_pfarg *arg)
{
	char	*d;

	d = va_arg(env->vali, char *);
	if (d == NULL)
	{
		arg->extra = 1;
		arg->len = (arg->prc == -2 || arg->prc > 6) ? 6 : arg->prc;
	}
	else
	{
		arg->len = ft_strlen(d);
		if (arg->prc >= 0 && arg->prc < arg->len)
			arg->len = arg->prc;
	}
	arg->fill = arg->fld - arg->len + 1;
	if (arg->flg.neg)
		fill_sneg(d, env, arg);
	else
		fill_sels(d, env, arg);
}
