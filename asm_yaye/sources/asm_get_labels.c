/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_labels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 13:33:22 by yaye              #+#    #+#             */
/*   Updated: 2020/07/31 13:33:23 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_labeldef(t_asm *a, char *s, size_t len)
{
	t_lb		*l;
	t_lb		*tmp;

	if (!(l = malloc(sizeof(t_lb))))
		leave(a, ": failed to malloc in get_labeldef().\n", 0);
	if (!(l->lb = malloc(sizeof(char) * len + 1)))
		leave(a, ": failed to malloc in get_labeldef().\n", 0);
	ft_strncpy(l->lb, s, len);
	l->lb[len] = 0;
	l->i_op = a->i;
	l->next = NULL;
	if (a->ldef == NULL)
		a->ldef = l;
	else
	{
		tmp = a->ldef;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = l;
	}
}

size_t	get_labelcall(t_asm *a, char *s, size_t byte_size, t_ope *ope)
{
	size_t		t;
	t_lb		*l;
	t_lb		*tmp;

	t = 0;
	while (ft_strchr(LABEL_CHARS, s[t]))
		t += 1;
	if (!(l = malloc(sizeof(t_lb))) \
		|| !(l->lb = malloc(sizeof(char) * t + 1)) || !ft_strncpy(l->lb, s, t))
		leave(a, ": failed to malloc in get_labelcall().\n", 0);
	l->lb[t] = 0;
	l->i_op = ope->i_op;
	l->i_call = a->i;
	l->byte_size = byte_size;
	l->next = NULL;
	if ((l->line = a->line) >= 0 && a->lcall == NULL)
		a->lcall = l;
	else
	{
		tmp = a->lcall;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = l;
	}
	return (t);
}
