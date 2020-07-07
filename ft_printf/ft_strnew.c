/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:24:39 by armajchr          #+#    #+#             */
/*   Updated: 2019/08/09 12:36:25 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*dest;

	if (!(dest = (char*)malloc(sizeof(char) * size + 1)))
		return (NULL);
	ft_bzero(dest, size + 1);
	return (dest);
}
