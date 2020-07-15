/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:26:53 by yaye              #+#    #+#             */
/*   Updated: 2020/07/03 15:26:54 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_in_binary(char c)
{
	int		x;
	char	d;

	x = 128;
	write(1, "0", 1);
	while (x > 1)
	{
		d = x - 1;
		if ((c / d) == 1)
		{
			c = c - d;
			write(1, "1", 1);
		}
		else
			write(1, "0", 1);
		x = x / 2;
	}
	write(1, " ", 1);
}

int		main(int ac, char **av)
{
	int		i;

	if (ac != 2)
		return (0);
	i = -1;
	while (av[1][++i])
		print_in_binary(av[1][i]);
	write(1, "\n\0", 2);
}
