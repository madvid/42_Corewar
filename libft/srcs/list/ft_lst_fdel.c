/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_fdel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:13:40 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/18 14:30:35 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** Function: ft_lst_fdel
** Description:
**	Delete function usefull for lstdel/lstdelone.
*/

void	ft_lst_fdel(void *link, size_t link_size)
{
	if (!link || link_size == 0)
		return ;
	((t_list*)link)->next = NULL;
	if (((t_list*)link)->cnt)
		free(((t_list*)link)->cnt);
	free(link);
	link = NULL;
}
