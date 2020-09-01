/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ascendingsort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:08:19 by yaye              #+#    #+#             */
/*   Updated: 2020/01/20 15:08:20 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_ascendingsort(int *tab, int len)
{
	int		i;
	int		j;
	int		min;

	i = -1;
	while (++i < len)
	{
		j = i;
		min = i;
		while (++j < len)
			if (tab[j] <= tab[min])
				min = j;
		j = tab[i];
		tab[i] = tab[min];
		tab[min] = j;
	}
}
