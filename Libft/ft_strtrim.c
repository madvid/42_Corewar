/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:45:50 by armajchr          #+#    #+#             */
/*   Updated: 2019/04/18 16:31:22 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strtrimcpy(char const *s, int j, int i, int l)
{
	char	*dst;
	int		k;

	k = 0;
	if (!(dst = (char*)malloc(sizeof(char) * l + 2)))
		return (NULL);
	while (j <= i)
	{
		dst[k] = s[j];
		k++;
		j++;
	}
	dst[k] = '\0';
	return (dst);
}

static char	*ft_empty(void)
{
	char *tmp;

	if (!(tmp = (char*)malloc(sizeof(char) * 1)))
		return (NULL);
	tmp[0] = '\0';
	return (tmp);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		l;

	if (!s)
		return (0);
	i = 0;
	j = 0;
	i = ft_strlen(s);
	i--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i--;
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		j++;
	l = i - j;
	if (l < 0)
		return (ft_empty());
	return (ft_strtrimcpy(s, j, i, l));
}
