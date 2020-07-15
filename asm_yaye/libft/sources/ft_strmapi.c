/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:18:51 by yaye              #+#    #+#             */
/*   Updated: 2019/04/04 18:18:52 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*fstr;

	if (!s || !f)
		return ((char *)NULL);
	i = 0;
	if (!(fstr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return ((char *)NULL);
	while (s[i])
	{
		fstr[i] = f(i, s[i]);
		i++;
	}
	fstr[i] = 0;
	return (fstr);
}
