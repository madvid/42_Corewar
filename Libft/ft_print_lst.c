/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:35:01 by armajchr          #+#    #+#             */
/*   Updated: 2019/04/15 12:14:06 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_print_lst(t_list *lst)
{
	if (lst == NULL)
	{
		ft_putstr("La liste est vide");
		return ;
	}
	while (lst)
	{
		ft_putstr(lst->content);
		ft_putchar(' ');
		lst = lst->next;
	}
}
