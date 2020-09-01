/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 13:10:53 by yaye              #+#    #+#             */
/*   Updated: 2019/07/30 13:10:54 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

void	to_b(unsigned long u, char *s, t_pfarg *arg)
{
	if (u < 2)
	{
		arg->len++;
		s[arg->i++] = u + '0';
	}
	else
	{
		arg->len++;
		to_b(u / 2, s, arg);
		s[arg->i++] = u % 2 + '0';
	}
}

void	fill_bneg(char *n, t_pf *env, t_pfarg *arg)
{
	int		i;

	if (arg->prc == 0 && n[0] == '0')
	{
		n[0] = 0;
		arg->len = 0;
	}
	arg->prc = (arg->prc < arg->len) ? 0 : arg->prc - arg->len;
	if (arg->extra && n[0] != '0')
	{
		if (arg->prc > 0)
			arg->prc = arg->prc - 1;
		fill_buf(env, arg->extra);
		arg->fill = arg->fld - (arg->prc++ + arg->len);
	}
	else
		arg->fill = arg->fld - (arg->prc++ + arg->len) + 1;
	while (--arg->prc > 0)
		fill_buf(env, '0');
	i = -1;
	while (n[++i])
		fill_buf(env, n[i]);
	while (--arg->fill > 0)
		fill_buf(env, ' ');
}

void	fill_bzro(char *n, t_pf *env, t_pfarg *arg)
{
	int		i;

	if (arg->extra && n[0] != '0')
	{
		if (arg->prc > 0)
			arg->prc = arg->prc - 1;
		fill_buf(env, arg->extra);
		arg->fill = arg->fld - arg->len;
	}
	else
		arg->fill = arg->fld - arg->len + 1;
	while (--arg->fill > 0)
		fill_buf(env, '0');
	i = -1;
	while (n[++i])
		fill_buf(env, n[i]);
}

void	fill_bels(char *n, t_pf *env, t_pfarg *arg)
{
	int		i;

	if (arg->prc == 0 && n[0] == '0')
	{
		n[0] = 0;
		arg->len = 0;
	}
	arg->prc = (arg->prc < arg->len) ? 0 : arg->prc - arg->len;
	if (arg->extra && arg->prc > 0 && n[0] != '0')
		arg->prc = arg->prc - 1;
	arg->fill = (arg->extra && n[0] != '0') ? arg->fld \
		- (arg->prc++ + arg->len) : arg->fld - (arg->prc++ + arg->len) + 1;
	while (--arg->fill > 0)
		fill_buf(env, ' ');
	if (arg->extra && n[0] != '0')
		fill_buf(env, arg->extra);
	while (--arg->prc > 0)
		fill_buf(env, '0');
	i = -1;
	while (n[++i])
		fill_buf(env, n[i]);
}

void	parse_b(t_pf *env, t_pfarg *arg)
{
	unsigned long	d;
	char			n[21];

	arg->extra = (arg->flg.hsh) ? '0' : 0;
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
	to_b(d, n, arg);
	if (arg->flg.neg)
		fill_bneg(n, env, arg);
	else if (arg->flg.zro)
		fill_bzro(n, env, arg);
	else
		fill_bels(n, env, arg);
}
