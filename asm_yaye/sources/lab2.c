/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lab2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 10:05:10 by yaye              #+#    #+#             */
/*   Updated: 2020/07/13 10:05:13 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#include <stdio.h>

void	upt_champion(t_asm *a, char *buf)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!(new = malloc(sizeof(char) \
		* (ft_strlen(a->chp) + ft_strlen(buf) + 1))))
	{
		release(a);
		leave(NULL, ": malloc failure in upt_champion().\n", 0);
	}
	i = 0;
	j = 0;
	if (a->chp)
		while (a->chp[i])
			new[j++] = a->chp[i++];
	i = 0;
	while (buf[i])
		new[j++] = buf[i++];
	new[j] = 0;
	if (a->chp)
	{
		ft_memset(a->chp, 0, ft_strlen(a->chp));
		ft_memdel((void **)&a->chp);
	}
	a->chp = new;
}

void	get_champion(t_asm *a, char **av)
{
	int				r;
	int				fd;
	char			buf[4096];

	r = -1;
	while (av[1][++r])
		if (!ft_isprint(av[1][r]))
			exit(write(2, "ERROR: unprintable character in filename.\n", 43));
	if (!ft_strequ(av[1] + r - 2, ".s"))
		exit(write(2, "ERROR: filename extension must be .s\n", 37));
	if ((fd = open(av[1], O_RDONLY)) < 0)
		exit(write(2, "ERROR: failed to open file.s\n", 29));
	a->chp = NULL;
	while ((r = read(fd, buf, 4095)) > 0 && !(buf[r] = 0))
		upt_champion(a, buf);
	close(fd);
	if (r < 0)
		leave(a, ": failed to read file.s\n", 0);
	ft_memset(a->cor, 0, COR_MAX);
	a->i = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	a->ldef = NULL;
	a->lcall = NULL;
	a->name = 0;
	a->comm = 0;
	a->line = 0;
}

void	fill_lcall(t_asm *a)
{
	t_lb		*cal;
	t_lb		*def;

	cal = a->lcall;
	while (cal)
	{
		def = a->ldef;
		while (def)
		{
			if (ft_strequ(def->lb, cal->lb))
				break ;
			def = def->next;
		}
		if (def == NULL)
		{
			write(2, "ERROR: LABEL CALLED DOES NOT EXIST.\n<", 37);
			write(2, cal->lb, ft_strlen(cal->lb));
			write(2, "> AT LINE: <", 12);
			ft_putnb(cal->line + 1);
			release(a);
			exit(write(2, ">\n", 2));
		}
		asto_bi(a, &cal->i_call, (def->i_op - cal->i_op), cal->byte_size);
		cal = cal->next;
	}
}

void	gen_cor(t_asm *a, char *filename)
{
	char	new[NAME_SIZE];
	int		len;
	int		i;

	if (!a)
		return ;
	ft_memset(new, 0, NAME_SIZE);
	len = ft_strlen(filename) - 2;
	if (len > NAME_SIZE - 5)
	{
		release(a);
		leave(NULL, ": NAME_SIZE EXCCEEDED, CHANGE THE VALUE ACCORDINGLY.\n", 0);
	}
	i = -1;
	while (++i < len)
		new[i] = filename[i];
	ft_strcat(new, ".cor");
	if ((i = open(new, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 3)
	{
		release(a);
		leave(NULL, ": FAILED TO CREATE championfile.cor\n", 0);
	}
	write(i, a->cor, a->i);
	close(i);
	ft_printf("Writing output program to %s\n", new);
}

int		main(int ac, char **av)
{
	extern t_op		op_tab[17];
	t_asm			a;
	int 			dummy;

	if (ac != 2)
		return (write(2, "Usage: ./asm <champion.s>\n", 26));
	a.op_tab = op_tab;
	get_champion(&a, av);						//def du t_asm a + read du .s
	dummy = 0;
	asto_bi(&a, &dummy, COREWAR_EXEC_MAGIC, 4);	//écriture du magic
	get_cor(&a);
	fill_lcall(&a);
	dummy = 136;
	asto_bi(&a, &dummy, a.size, 4);
	gen_cor(&a, av[1]);
	release(&a);
}
