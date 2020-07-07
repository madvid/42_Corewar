/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:16:20 by armajchr          #+#    #+#             */
/*   Updated: 2019/09/10 14:28:25 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <string.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	unsigned int i;

	i = 0;
	if (!s || s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
