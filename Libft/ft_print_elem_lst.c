/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_elem_lst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:31:15 by armajchr          #+#    #+#             */
/*   Updated: 2019/04/15 12:15:42 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_print_elem_lst(t_list *lst)
{
	if (lst == NULL)
	{
		ft_putstr("L'element est vide");
		return ;
	}
	ft_putstr(lst->content);
}
