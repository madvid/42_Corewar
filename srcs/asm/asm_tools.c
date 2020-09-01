/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 10:09:33 by yaye              #+#    #+#             */
/*   Updated: 2020/09/01 17:54:53 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"

void	ft_putnb(size_t n)
{
	char	c;

	if (n < 10)
	{
		c = n + '0';
		write(2, &c, 1);
	}
	else
	{
		ft_putnb(n / 10);
		c = n % 10 + '0';
		write(2, &c, 1);
	}
}

/*
** FREES ALL ALLOCATED MEMORY IN THE PROGRAM
*/

void	release(t_asm *a)
{
	t_lb		*tmp1;
	t_lb		*tmp2;

	if (a->chp)
		ft_memdel((void **)&a->chp);
	tmp1 = a->ldef;
	tmp2 = a->lcall;
	while (a->ldef)
	{
		tmp1 = a->ldef->next;
		ft_memdel((void **)&a->ldef->lb);
		ft_memdel((void **)&a->ldef);
		a->ldef = tmp1;
	}
	while (a->lcall)
	{
		tmp1 = a->lcall->next;
		ft_memdel((void **)&a->lcall->lb);
		ft_memdel((void **)&a->lcall);
		a->lcall = tmp1;
	}
}

/*
** LEAVES THE PROGRAM AFTER RELEASING ALL ALLOCATED MEMORY WITH release()
** THEN WRITES AN ERROR MESSAGE IN THE STANDARD ERROR
*/

void	leave(t_asm *a, char *s, size_t col)
{
	write(2, "ERROR", 5);
	if (s)
		write(2, s, ft_strlen(s));
	else
		write(2, "\n", 1);
	if (a)
	{
		release(a);
		write(2, "LINE: <", 7);
		ft_putnb(a->line + 1);
		write(2, ">", 1);
	}
	else
		exit(EXIT_FAILURE);
	if (col != 0)
	{
		write(2, " COL: <", 7);
		ft_putnb(col + 1);
		write(2, ">\n", 2);
	}
	else
		write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

/*
** WRITES THE BYTE VALUE c AT POSITION *i IN bytes NUMBER OF BYTES
** USED TO WRITE THE MAGIC NUMBER AT THE BEGINNING OF a->cor WHEN c == 0
*/

void	asto_bi(t_asm *a, int *i, int c, int bytes)
{
	size_t	n;

	n = ft_power(16, bytes * 2 - 1);
	while (n != 0)
	{
		if (*i >= COR_MAX)
			leave(a, ": .COR STACK-OVERFLOW.\n", 0);
		a->cor[*i] = c / n * 16;
		c = c % n;
		n = n / 16;
		a->cor[*i] += c / n;
		c = c % n;
		n = n / 16;
		*i += 1;
	}
	a->size += bytes;
}

size_t	is_endline(t_asm *a, char *s)
{
	size_t	t;

	t = 0;
	while (s[t] && s[t] != '\n')
	{
		if (s[t] == COMMENT_CHAR || s[t] == ';')
			while (s[t] && s[t] != '\n')
				t += 1;
		else if (s[t] != ' ' && s[t] != '\t' && s[t] != '\v')
		{
			if (a)
				leave(a, ": SYNTAX ERROR.\n", t);
			return (t);
		}
		else
			t += 1;
	}
	if (s[t] == '\n' && (t += 1) > 0)
	{
		if (a)
			a->line += 1;
		while (s[t] == ' ' || s[t] == '\t' || s[t] == '\v')
			t += 1;
	}
	return (t);
}
