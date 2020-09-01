/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:24:25 by yaye              #+#    #+#             */
/*   Updated: 2019/04/08 16:24:32 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_strsplit_lst(char const *s, char c)
{
	char	**tab;
	size_t	i;
	t_list	*list;
	t_list	*ret;

	if (!(tab = ft_strsplit(s, c)))
		return (NULL);
	list = ft_lstnew(tab[0], ft_strlen(tab[0]));
	ret = list;
	i = 1;
	while (tab[i])
	{
		(*list).next = ft_lstnew(tab[i], ft_strlen(tab[i]));
		list = (*list).next;
		i++;
	}
	(*list).next = NULL;
	return (ret);
}
