/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:52:00 by yaye              #+#    #+#             */
/*   Updated: 2020/08/07 13:52:01 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

void	leave(t_dasm *a, char *s)
{
	write(2, "ERROR", 5);
	if (s)
		write(2, s, ft_strlen(s));
	else
		write(2, "\n", 1);
	ft_memset(a->chp, 0, CHP_SIZE);
	ft_memset(a->cor, 0, COR_MAX);
	exit(EXIT_FAILURE);
}

void	get_champion(t_dasm *a, char **av)
{
	int				r;
	int				fd;
	char			buf[4096];
	int				i;
	int				j;

	r = -1;
	while (av[1][++r])
		if (!ft_isprint(av[1][r]))
			exit(write(2, "ERROR: unprintable character in filename.cor\n", 45));
	if (!ft_strequ(av[1] + r - 4, ".cor"))
		exit(write(2, "ERROR: filename extension must be .cor\n", 37));
	if ((fd = open(av[1], O_RDONLY)) < 0)
		exit(write(2, "ERROR: failed to open file.cor\n", 29));
	i = 0;
	while ((r = read(fd, buf, 4095)) > 0)
	{
		j = 0;
		while (j < r)
			a->cor[i++] = buf[j++];
	}
	close(fd);
	if (r < 0)
		leave(a, ": failed to read file.cor\n");
}

void	gen_s(t_dasm *a, char *filename)
{
	char	new[NAME_SIZE];
	int		len;
	int		i;

	ft_memset(new, 0, NAME_SIZE);
	len = ft_strlen(filename) - 4;
	if (len > NAME_SIZE - 3)
		leave(a, ": NAME_SIZE EXCCEEDED.\n");
	i = -1;
	while (++i < len)
		new[i] = filename[i];
	ft_strcat(new, ".s");
	if ((i = open(new, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 3)
		leave(NULL, ": FAILED TO CREATE championfile.s\n");
	write(i, a->chp, ft_strlen(a->chp));
	close(i);
	ft_printf("Writing output program to %s\n", new);
}

int		main(int ac, char **av)
{
	extern t_op		op_tab[17];
	t_dasm			a;

	if (ac != 2)
	{
		write(2, "Usage: ./dasm <champion.cor>\n", 29);
		return (0);
	}
	a.op_tab = op_tab;
	get_champion(&a, av);
	get_s(&a);
	gen_s(&a, av[1]);
	ft_memset(a.chp, 0, CHP_SIZE);
	ft_memset(a.cor, 0, COR_MAX);
}
