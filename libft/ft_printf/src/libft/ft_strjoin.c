/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 13:57:02 by weilin            #+#    #+#             */
/*   Updated: 2018/11/20 14:32:34 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *j;

	if (!s1 || !s2)
		return (NULL);
	if (!(j = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	j = ft_strcat(ft_strcpy(j, s1), s2);
	return (j);
}
