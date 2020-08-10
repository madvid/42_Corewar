/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1d_int_tabledel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 11:50:33 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/07 11:53:17 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** Function: ft_1d_int_tabledel
** Description:
**	Frees a 1D int table of <nb_elem> elements.
*/

void		ft_1d_int_tabledel(int **tab, int nb_elem)
{
	int		i;

	i = -1;
	while (++i <= nb_elem)
		(*tab)[i] = 0;
	free(*tab);
	tab = NULL;
}
