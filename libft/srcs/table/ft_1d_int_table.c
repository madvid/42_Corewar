/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1D_int_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 18:28:18 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/22 18:47:05 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** Function: ft_1D_int_table
** Description:
**	Allocates a 1D int table of <nb_elem> elements.
** Return:
**	int* :
**	NULL :
*/

int		*ft_1d_int_table(int nb_elem)
{
	int		*table;
	int		i;

	i = 0;
	table = NULL;
	if (nb_elem <= 0)
		return (NULL);
	if (!(table = (int*)malloc(sizeof(int) * nb_elem)))
		return (NULL);
	while (i < nb_elem)
	{
		table[i] = 0;
		i++;
	}
	return (table);
}
