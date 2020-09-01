/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:56:54 by yaye              #+#    #+#             */
/*   Updated: 2019/04/05 19:56:55 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lst;

	if (!(lst = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		(*lst).content = NULL;
		(*lst).content_size = 0;
	}
	else
	{
		if (!((*lst).content = malloc(sizeof(content) * content_size)))
			return (NULL);
		(*lst).content = ft_memcpy((*lst).content, content, content_size);
		(*lst).content_size = content_size;
	}
	(*lst).next = NULL;
	return (lst);
}
