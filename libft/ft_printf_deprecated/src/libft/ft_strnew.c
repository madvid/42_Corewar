/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 18:17:44 by weilin            #+#    #+#             */
/*   Updated: 2018/11/19 18:36:28 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *s;

	if (!(s = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	s[size] = 0;
	while (size--)
		s[size] = 0;
	return (s);
}
