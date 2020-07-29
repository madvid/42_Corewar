/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1d_int_table_set.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 10:51:42 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/23 11:00:02 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_1d_int_table_set(int *table, int nb, size_t ini, size_t width)
{
	size_t		i;

	i = 0;
	while (i < width)
	{
		table[ini + i] = nb;
		i++;
	}
}
