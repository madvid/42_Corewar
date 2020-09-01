/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:51:49 by yaye              #+#    #+#             */
/*   Updated: 2020/02/20 15:51:50 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** str IS SUPPOSED TO BE AN INT [-2147483648; 2147483647]
** i IS THE ADDRESS IN WHICH IS SAVED THE CONVERSION IF DONE CORRECTLY
** c IS THE SEPARATOR NOTIFYING WHERE THE NUMBER END IN str
** RETURN (j == LENGHT OF THE INT) IF SUCCESSFULLY CONVERTED *str TO INT IN *i
** RETURN 0 IF IT FAILED BECAUSE:
** 		str IS NOT AN INT
** 		str IS NOT TERMINATED BY \0 or c
** 		str > MAX_INT or str < MIN_INT
*/

size_t		ft_stoi(char *str, int *i, char c)
{
	size_t			j;
	int				m;
	unsigned int	n;

	j = 0;
	if (!str)
		return (0);
	if (str[j] != '-' && str[j] != '+' && !ft_isdigit(str[j]))
		return (0);
	m = (str[j] == '-') ? -1 : 1;
	if (!(n = 0) && !ft_isdigit(str[j]) && !ft_isdigit(str[++j]))
		return (0);
	while (ft_isdigit(str[j]))
		if (n > 214748364 || \
			((n = n * 10 + str[j++] - '0') > 2147483647 && m > 0) \
			|| (n > 2147483648 && m < 0))
			return (0);
	if (str[j] && ((c == '\t' && !ft_isblanc(str[j])) \
		|| (c != '\t' && str[j] != c)))
		return (0);
	if (i)
		*i = m * (int)n;
	return (j);
}
