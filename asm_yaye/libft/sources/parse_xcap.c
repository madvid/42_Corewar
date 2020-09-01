/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xcap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:52:10 by yaye              #+#    #+#             */
/*   Updated: 2019/07/25 15:52:12 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

void	to_xcap(unsigned long u, char *s, t_arg *arg)
{
	char	*base;

	base = "0123456789ABCDEF";
	if (u < 16)
	{
		arg->len++;
		s[arg->i++] = base[u];
	}
	else
	{
		arg->len++;
		to_xcap(u / 16, s, arg);
		s[arg->i++] = base[u % 16];
	}
}

void	fill_xcapneg(char *n, t_pf *env, t_arg *arg)
{
	int		i;

	if (arg->prc >= 0 && n[0] == '0')
		arg->len = 0;
	arg->prc = (arg->prc < arg->len) ? 0 : arg->prc - arg->len;
	if (arg->extra && n[0] != '0')
	{
		fill_buf(env, '0');
		fill_buf(env, arg->extra);
		arg->fill = arg->fld - (arg->prc++ + arg->len) - 1;
	}
	else
		arg->fill = arg->fld - (arg->prc++ + arg->len) + 1;
	while (--arg->prc > 0)
		fill_buf(env, '0');
	i = -1;
	while (++i < arg->len)
		fill_buf(env, n[i]);
	while (--arg->fill > 0)
		fill_buf(env, ' ');
}

void	fill_xcapzro(char *n, t_pf *env, t_arg *arg)
{
	int		i;

	if (arg->extra && n[0] != '0')
	{
		fill_buf(env, '0');
		fill_buf(env, arg->extra);
		arg->fill = arg->fld - arg->len - 1;
	}
	else
		arg->fill = arg->fld - arg->len + 1;
	while (--arg->fill > 0)
		fill_buf(env, '0');
	i = -1;
	while (++i < arg->len)
		fill_buf(env, n[i]);
}

void	fill_xcapels(char *n, t_pf *env, t_arg *arg)
{
	int		i;

	if (arg->prc >= 0 && n[0] == '0')
	{
		arg->extra = 0;
		arg->len = 0;
	}
	arg->prc = (arg->prc < arg->len) ? 0 : arg->prc - arg->len;
	arg->fill = (arg->extra) ? arg->fld - (arg->prc++ + arg->len) - 1 \
		: arg->fld - (arg->prc++ + arg->len) + 1;
	while (--arg->fill > 0)
		fill_buf(env, ' ');
	if (arg->extra && n[0] != '0')
	{
		fill_buf(env, '0');
		fill_buf(env, arg->extra);
	}
	while (--arg->prc > 0)
		fill_buf(env, '0');
	i = -1;
	while (++i < arg->len)
		fill_buf(env, n[i]);
}

void	parse_xcap(t_pf *env, t_arg *arg)
{
	unsigned long	d;
	char			n[21];

	arg->extra = (arg->flg.hsh) ? 'X' : 0;
	if (arg->prc >= 0)
		arg->flg.zro = 0;
	if (arg->mod >= 3)
		d = (unsigned long)va_arg(env->vali, intmax_t);
	else if (arg->mod == 2)
		d = (unsigned short)va_arg(env->vali, intmax_t);
	else if (arg->mod == 1)
		d = (unsigned char)va_arg(env->vali, intmax_t);
	else
		d = va_arg(env->vali, unsigned int);
	ft_bzero(n, 21);
	to_xcap(d, n, arg);
	if (arg->flg.neg)
		fill_xcapneg(n, env, arg);
	else if (arg->flg.zro)
		fill_xcapzro(n, env, arg);
	else
		fill_xcapels(n, env, arg);
}
