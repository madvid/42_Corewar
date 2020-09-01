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

/*
** Writes error message
** Resets champion_s[] and chamion_cor[] to 0
** Exits program 
*/

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

/*
** Checks name input is printable and has .cor extension
** Opens it
** Read and save it in a->cor[]
*/

void	get_champion_cor(t_dasm *a, char **av)
{
	int				r;
	int				fd;
	char			buf[COR_MAX];
	int				i;

	r = -1;
	while (av[1][++r])
		if (!ft_isprint(av[1][r]))
			exit(write(2, "ERROR: unprintable char in filename.cor\n", 40));
	if (!ft_strequ(av[1] + r - 4, ".cor"))
		exit(write(2, "ERROR: filename extension must be .cor\n", 37));
	if ((fd = open(av[1], O_RDONLY)) < 0)
		exit(write(2, "ERROR: failed to open file.cor\n", 29));
	i = -1;
	if ((r = read(fd, buf, COR_MAX - 1)) > 0)
		while (++i < r)
			a->cor[i] = buf[i];
	close(fd);
	if (r < 0)
		leave(a, ": failed to read file.cor\n");
	a->cor[r] = 0;
}

/*
** Writes the .s conversion from a->chp in championfile.s
*/

void	generate_champion_s(t_dasm *a, char *filename)
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
	write(1, "Writing output program to ", 26);
	write(1, new, ft_strlen(new));
	write(1, "\n", 1);
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
	get_champion_cor(&a, av);
	get_s(&a);
	generate_champion_s(&a, av[1]);
	ft_memset(a.chp, 0, CHP_SIZE);
	ft_memset(a.cor, 0, COR_MAX);
}
