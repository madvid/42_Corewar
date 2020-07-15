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
#include <unistd.h>		//write read
#include <stdlib.h>		//EXIT_FAILURE
#include <fcntl.h>		//open

void	release(t_asm *a)
{
	if (a->chp)
		ft_memdel((void **)&a->chp);
	ft_memset(a->cor, 0, COR_MAX);
}

/*
** LEAVES THE PROGRAM AFTER RELEASING ALL ALLOCATED MEMORY
*/

void	leave(t_asm *a, char *s)
{
	release(a);
	write(2, "ERROR", 5);
	if (s)
		write(2, s, ft_strlen(s));
	else
		write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

#include <stdio.h>
void	print_core(t_asm *a, char **av)
{
	//int		fd;
	char	test[128];
	int		i;
	FILE 	*fichier;

	i = 0;
	while (av[1][i] && av[1][i] != '.')
	{
		test[i] = av[1][i];
		i += 1;
	}
	if (av[1][i] != '.')
		leave(a, NULL);
	test[i++] = '.';
	test[i++] = 'c';
	test[i++] = 'o';
	test[i++] = 'r';
	test[i++] = 0;
	/*if ((fd = open(test, O_WRONLY | O_CREAT | O_APPEND)) < 0)
		leave(a, ": failed to open file.cor\n");
	write(fd, a->cor, COR_MAX);*/
	fichier = fopen("./test", "a");
	fwrite(a->cor, COR_MAX, 1, fichier);
	i = 0;
	while (i < (128 + 4) * 8)
	{
		ft_printf("%d", a->cor[i]);
		if (i % 40 == 39)
			ft_printf("\n");
		else if (i % 8 == 7)
			ft_printf(" ");
		i = i + 1;
	}
	//close(fd);
}

/*
** WRITES THE EQUIVALENT BINARY OF c AT THE END OF a->cor
** USED TO WRITE THE MAGIC NUMBER AT THE BEGINNING OF a->cor WHEN magic == 1
*/

void	to_core(t_asm *a, size_t *i, size_t c)
{
	size_t	n;

	if (c == 0)
	{
		if (COREWAR_EXEC_MAGIC > 0xffffff)
			leave(a, ": COREWAR_EXEC_MAGIC EXCEEDS 0xffffff\n");
		n = 2147483648;
		c = COREWAR_EXEC_MAGIC;
	}
	else
		n = ft_power(2, 7);
	while (n != 0)
	{
		a->cor[*i] = ((c & n) != 0);
		*i += 1;
		n = n / 2;
	}
}

void	upt_champion(t_asm *a, char *buf)
{
	size_t	new_len;
	char	*new;
	size_t	i;
	size_t	j;

	new_len = ft_strlen(a->chp) + ft_strlen(buf) + 1;
	if (!(new = malloc(sizeof(char) * new_len)))
		leave(a, ": malloc failure in get_champion().\n");
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
	int		fd;
	int		r;
	char	buf[4096];
	size_t	i;

	if (!a)
		exit(write(2, "ERROR\n", 6));					//au cas où ?
	if ((fd = open(av[1], O_RDONLY)) < 0)
		exit(write(2, "ERROR: failed to open file.s\n", 29));
	a->chp = NULL;
	while ((r = read(fd, buf, 4095)) > 0)
	{
		buf[r] = 0;
		upt_champion(a, buf);
	}
	close(fd);
	if (r < 0)
		leave(a, ": failed to read file.s\n");
	ft_memset(a->cor, 0, COR_MAX);
	a->name = 0;
	a->comm = 0;
	i = 0;
	to_core(a, &i, 0);
}

size_t	is_com(char *s)
{
	size_t	t;

	t = 0;
	if (*s == '#')
	{
		while (s[t] && s[t] != '\n')
			t += 1;
		while (s[t] == '\f' || s[t] == '\t' || s[t] == ' '  \
			|| s[t] == '\n' || s[t] == '\r' || s[t] == '\v')
			t += 1;
	}
	return (t);
}

size_t	is_endline(t_asm *a, char *s)
{
	size_t	t;

	t = 0;
	while (s[t] && s[t] != '\n')
	{
		if (s[t] == '#')
			while (s[t] && s[t] != '\n')
				t += 1;
		else if (s[t] != ' ' && s[t] != '\t' && s[t] != '\v')
			leave(a, ": SYNTAX ERROR BEFORE END OF LINE.\n");
		else
			t += 1;
	}
	if (s[t] == '\n')
		while (s[t] == ' ' || s[t] == '\t' || s[t] == '\v')
			t += 1;
	return (t);
}

size_t	get_hname(t_asm *a, char *s)
{
	size_t	t;		//indice parcourant le "nom" du .s
	size_t	i;		//indice parcourant le "nom" du .cor
	size_t	len;

	if (a->name++ == 1)										//si on a déjà vu .name
		leave(a, ": MULTIPLE NAME_CMD_STRING COMMAND.\n");
	t = ft_strlen(NAME_CMD_STRING);							//s[t] == le caratère juste après ".name"
	while (s[t] == ' ' || s[t] == '\t' || s[t] == '\v')		//on ignore les blancs
		t += 1;
	if (s[t++] != '"')										//après les blancs, s[t] == " sinon erreur
		leave(a, ": SYNTAX ERROR AT TOKEN COMMAND NAME_CMD_STRING.\n");
	i = 4 * 8;												//position du premier bit du name dans .cor
	len = t;
	while (s[t] && t <= (len + PROG_NAME_LENGTH)\
		&& s[t] != '"' && (ft_isprint(s[t]) || ft_isblanc(s[t])))
		to_core(a, &i, s[t++]); //on traduit chaque s[t] dans "nom de champion" qu'on ajoute dans a->cor directement en binaire
	if (t > (len + PROG_NAME_LENGTH))
		leave(a, ": PROG_NAME_LENGTH EXCEEDED.\n"); //si on dépasse le PROG_NAME_LENGTH alors erreur
	else
		while (i < (4 + PROG_NAME_LENGTH) * 8)			//sinon on remplit le reste de 00000000 (pas obligé vu qu'on set tout à 0)
			a->cor[i++] = 0;
	if (s[t++] != '"')								//si s[t] != " alors erreur (guillement fermante)
		leave(a, ": SYNTAX ERROR AT TOKEN COMMAND NAME_CMD_STRING.\n");
	return (t);
}

size_t	is_hname(t_asm *a, char *s)
{
	size_t	t;

	t = 0;
	if (ft_strnequ(s, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))	//si *s == ".name"
	{
		t = get_hname(a, s);		//t pointe sur le char après les guillemets fermantes
		//t = is_endline(a, s);
	}
	return (t);
}

size_t	is_hcomment(t_asm *a, char *s)			//+ "get_hname()" 
{
	size_t	t;		//indice parcourant le "nom" du .s
	size_t	i;		//indice parcourant le "nom" du .cor
	size_t	len;

	t = 0;
	if (ft_strnequ(s, COMMENT_CMD_STRING, 8))		//si je trouve ".comment"
	{
		if (a->comm++ == 1)							//si on a déjà eu un ".comment" alors erreur
			leave(a, ": MULTIPLE COMMENT_CMD_STRING COMMAND.\n");
		t = ft_strlen(COMMENT_CMD_STRING);			//on se met au char juste après le "t" de ".comment"
		while (s[t] == ' ' || s[t] == '\t' || s[t] == '\v')	//on ignore les espaces et tabulations
			t += 1;
		if (s[t++] != '"')									//après les espaces/tabs, si on n'a pas de " alors erreur
			leave(a, ": SYNTAX ERROR AT TOKEN COMMAND COMMENT_CMD_STRING.\n");
		i = 140 * 8;								//position du premier bit de comment dans .corlen = t
		len = t;
		while (s[t] && t <= (len + COMMENT_LENGTH) \
			&& s[t] != '"' && (ft_isprint(s[t]) || ft_isblanc(s[t])))
			to_core(a, &i, s[t++]);
		if (t > (len + COMMENT_LENGTH))
			leave(a, ": COMMENT_LENGTH EXCEEDED.\n");
		else
			while (i < (140 + PROG_NAME_LENGTH) * 8)	//sinon on remplit le reste de 00000000	(pas obligé vu qu'on set tout à 0)
				a->cor[i++] = 0;
		if (s[t++] != '"')								//si s[t] != " alors erreur (guillement fermante)
			leave(a, ": SYNTAX ERROR AT TOKEN COMMAND NAME_CMD_STRING.\n");
	}
	return (t);
}

int		ft_strchrf(char *s, int c, int i)
{
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/*size_t	is_ins(t_asm *a, char *s)
{
	size_t	t;

	t = 0;
	while (s[t])
	{
		while (ft_strchrf(LABEL_CHARS, s[t], 0) >= 0)
			t++;
		if (s[t] == ':')
			get_label();
		if (!is_op(a, s, t))
	}
	return (t);
}*/

/*void	parse(t_asm *a)
{
	size_t	i;
	size_t	t;

	i = 0;
	while (a->chp[i])
	{
		if ((t = is_ignore()) > 0)
			i += t;
		else if ((t = is_hname(a, a->chp + i)) > 0)
			i += t;
		else if ((t = is_hcomment(a, a->chp + i)) > 0)
			i += t;
		else if ((t = is_ins(a, a->chp + i)) > 0)
			i += t;
		else
			leave(a, NULL);
	}
}*/

int		main(int ac, char **av)
{
	t_asm	a;

	if (ac != 2)
		return (write(2, "Usage: ./asm <champion.s>\n", 26));
	//a.op_tab[0] = {"live", 1, {T_DIR}, 1, 10, "alive", 0, 0};
	get_champion(&a, av);
	//parse(&a);
	int 	i;

	i = 0;
	while (a.chp[i])
	{
		is_hname(&a, a.chp + i);
		i = i + 1;
	}
	//print_core(&a, av);
	release(&a);
}
