/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_di.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:59:08 by mdavid            #+#    #+#             */
/*   Updated: 2020/02/26 09:03:10 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FONCTION: ft_plus_space_for_int
** PARAMETERS:	t_data *t: main struct of data.
** 				int sign: sign of the integer received as parameter.
** 				char **val: adress of the number as a string
** DESCRIPTION:
** 	Generate new string made of '+'/' '/'-' and the number as string if
** 	flag.plus = 1.
** If the sign of the number is negative, the sign '+' is not add.
** RETURN:
** 	(int)STAT_OK if everything ok.
** 	(int)STAT_ERR if there is a pb in mem allocation return error.
*/

int		ft_plus_space_for_int(t_data *t, char **val, int neg)
{
	int		tot;
	char	*mps;
	char	*tmp;

	tot = neg * 100 + t->flag.plus * 10 + t->flag.space;
	mps = (tot < 10) ? " " : "+";
	(tot >= 100) ? mps = "-" : 0;
	if (tot != 0)
	{
		if (!(tmp = ft_strjoin(mps, *val)))
			return ((int)STAT_ERR);
		*val = ft_strreset(*val, tmp);
	}
	return ((int)STAT_OK);
}

/*
** FONCTION: ft_minus_for_int
** PARAMETERS:	t_data *t: pointer on the principal variable structure.
** 				char **val: adress of the number as a string
** DESCRIPTION:
** 	Generate new string taking into account flag.zero and the string val.
** 	If flag->minus = 1 flag.zero is ignored, else
** RETURN:
** 	(int)STAT_OK if everything ok.
** 	(int)STAT_ERR if there is a pb in mem allocation return error.
*/

int		ft_minus_for_int(t_data *t, char **val, char **str_w, int neg)
{
	char	*tmp;
	int		i;

	if (t->flag.zero == 0 || t->flag.minus == 1)
		i = ft_plus_space_for_int(t, val, neg);
	else
		i = ft_plus_space_for_int(t, str_w, neg);
	if (t->flag.minus == 1)
	{
		if (i == (int)STAT_ERR || !(tmp = ft_strjoin(*val, *str_w)))
			return ((int)STAT_ERR);
	}
	else
	{
		if (i == (int)STAT_ERR || !(tmp = ft_strjoin(*str_w, *val)))
			return ((int)STAT_ERR);
	}
	str_w ? ft_strdel(str_w) : 0;
	if (i == (int)STAT_ERR || tmp)
		*val = ft_strreset(*val, tmp);
	else if (i == (int)STAT_ERR || !(*val = ft_strdup("")))
		return ((int)STAT_ERR);
	return ((int)STAT_OK);
}

/*
** FONCTION: ft_prec_for_int
** PARAMETERS:	t_data *t: main struct of data.
** 				char **val: adress of the number as a string
** DESCRIPTION:
** 	Treat flag prec.
** RETURN:
** 	(int)STAT_OK if everything ok.
** 	(int)STAT_ERR if there is a pb in mem allocation return error.
*/

int		ft_prec_for_int(t_data *t, char **val)
{
	int		len_diff;
	char	*tmp;
	char	*ctmp;

	len_diff = t->flag.prec - (int)ft_strlen(*val);
	if (len_diff > 0)
	{
		if (!(ctmp = ft_strnew_c((size_t)len_diff, '0')))
			return ((int)STAT_ERR);
		if (!(tmp = ft_strjoin(ctmp, *val)))
			return ((int)STAT_ERR);
		free(ctmp);
		*val = ft_strreset(*val, tmp);
		t->flag.zero = 0;
	}
	if (t->flag.prec == 0 && ft_strcmp(*val, "0") == 0)
	{
		if (!(*val = ft_strdup("")))
			return ((int)STAT_ERR);
	}
	return ((int)STAT_OK);
}

/*
** FONCTION: ft_width_for_int
** PARAMETERS:	t_data *t: main struct of data.
** 				char **val: adress of the number as a string.
** 				size_t len: length of the string *val.
** 				int neg: signe of the number (1:negative, 0:positive).
** DESCRIPTION:
** 	Treat flag width, taking into acount flags '+',' ','-' and sign of val.
** RETURN:
** 	(int)STAT_OK if everything ok.
** 	(int)STAT_ERR if there is a pb in mem allocation return error.
*/

int		ft_width_for_int(t_data *t, char **val, size_t len, int neg)
{
	int		len_diff;
	char	*str_w;
	char	zerospace;

	len_diff = t->flag.width - (int)len;
	zerospace = (t->flag.zero == 1 && t->flag.minus == 0) ? '0' : ' ';
	(t->flag.plus == 1 || t->flag.space == 1 || neg == 1) ? len_diff -= 1 : 0;
	if (len_diff > 0)
	{
		if (!(str_w = ft_strnew_c((size_t)len_diff, zerospace))
			|| ft_minus_for_int(t, val, &str_w, neg) == (int)STAT_ERR)
		{
			(str_w) ? free(str_w) : 0;
			return ((int)STAT_ERR);
		}
	}
	else
		return (ft_plus_space_for_int(t, val, neg));
	return ((int)STAT_OK);
}

/*
** FONCTION: type_int
** PARAMETERS:	t_data *t: main struct of data.
** DESCRIPTION:
** 	Treat the  int conversion, proccessing flags before calling function
** 	print_int.
** RETURN:
** 	nothing.
*/

void	type_int(t_data *t)
{
	long int		n;
	int				neg;
	char			*val;

	(t->flag.prec >= 0) ? t->flag.zero = 0 : 0;
	init_int_arg(t, &n);
	neg = (n < 0) ? 1 : 0;
	val = (neg == 1) ? ft_ulltoa(-n) : ft_ulltoa(n);
	if (ft_prec_for_int(t, &val) == (int)STAT_ERR ||
		(ft_width_for_int(t, &val, ft_strlen(val), neg) == (int)STAT_ERR))
	{
		(val) ? ft_strdel(&val) : 0;
		return ;
	}
	if (!(val))
		return ;
	t->bf = val;
	print_int(t);
}
