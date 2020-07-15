/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:22:57 by yaye              #+#    #+#             */
/*   Updated: 2019/04/04 17:22:58 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (!(mem = (void *)malloc(sizeof(void) * size)))
		return ((void *)NULL);
	mem = ft_memset(mem, 0, size);
	return (mem);
}
