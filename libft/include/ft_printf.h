/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:37:37 by weilin            #+#    #+#             */
/*   Updated: 2020/08/28 10:28:21 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdint.h>
# define PF_BUF 5000

/*
** >------------------------------ FT_PRINTF ---------------------------------<
*/

typedef struct		s_pf
{
	va_list			vali;
	char			str[PF_BUF];
	int				i;
	int				len;
}					t_pf;

typedef struct		s_flg
{
	int				hsh;
	int				spc;
	int				pls;
	int				zro;
	int				neg;
}					t_flg;

typedef	struct		s_pfarg
{
	t_flg			flg;
	int				fld;
	int				prc;
	int				mod;
	int				typ;
	int				len;
	int				fill;
	int				extra;
	int				i;
	char			*p;
	char			f[81];
	char			inf[81];
	char			nan[81];
}					t_pfarg;

int					ft_printf(const char *str, ...);
void				fill_buf(t_pf *env, char c);
void				new_arg(t_pfarg *new);
void				to_u(unsigned long u, char *s, t_pfarg *arg);
void				to_bi(long double f, char *s);
int					parse(const char *str, t_pf *env);
void				parse_di(t_pf *env, t_pfarg *arg);
void				parse_o(t_pf *env, t_pfarg *arg);
void				parse_u(t_pf *env, t_pfarg *arg);
void				parse_x(t_pf *env, t_pfarg *arg);
void				parse_xcap(t_pf *env, t_pfarg *arg);
void				parse_c(t_pf *env, t_pfarg *arg);
void				parse_s(t_pf *env, t_pfarg *arg);
void				parse_p(t_pf *env, t_pfarg *arg);
void				parse_f(t_pf *env, t_pfarg *arg);
void				parse_percent(t_pf *env, t_pfarg *arg);
void				parse_b(t_pf *env, t_pfarg *arg);
int					naninf(long double n, char *s, t_pfarg *arg);

#endif
