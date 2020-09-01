/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:30:55 by yaye              #+#    #+#             */
/*   Updated: 2020/09/01 17:31:58 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_printf.h"
#include "libft.h"

void	to_o(unsigned long u, char *s, t_pfarg *arg)
{
	if (u < 8)
	{
		arg->len++;
		s[arg->i++] = u + '0';
	}
	else
	{
		arg->len++;
		to_o(u / 8, s, arg);
		s[arg->i++] = u % 8 + '0';
	}
}

void	fill_oneg(char *n, t_pf *env, t_pfarg *arg)
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

void	fill_ozro(char *n, t_pf *env, t_pfarg *arg)
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

void	fill_oels(char *n, t_pf *env, t_pfarg *arg)
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

void	parse_o(t_pf *env, t_pfarg *arg)
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
	to_o(d, n, arg);
	if (arg->flg.neg)
		fill_oneg(n, env, arg);
	else if (arg->flg.zro)
		fill_ozro(n, env, arg);
	else
		fill_oels(n, env, arg);
}
