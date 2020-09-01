/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:09:31 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/10 14:50:56 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t		ft_strlen(const char *str)
{
	unsigned int		i;

	i = 0;
	if (str == NULL || !str)
		return (i);
	while (str[i])
		i++;
	return (i);
}
