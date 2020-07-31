/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_cor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 13:25:45 by yaye              #+#    #+#             */
/*   Updated: 2020/07/31 13:25:47 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

size_t	is_hname(t_asm *a, char *s)
{
	size_t	t;
	int		i;
	size_t	len;

	t = 0;
	if (!ft_strnequ(s, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		return (0);
	if (a->name++ == 1)
		leave(a, ": MULTIPLE NAME_CMD_STRING COMMAND.\n", 0);
	t = ft_strlen(NAME_CMD_STRING);
	while (s[t] == ' ' || s[t] == '\t' || s[t] == '\v')
		t += 1;
	if (s[t++] != '"')
		leave(a, ": SYNTAX ERROR AT COMMAND NAME_CMD_STRING.\n", 0);
	i = 4;
	len = t;
	while (s[t] && t <= (len + PROG_NAME_LENGTH)\
		&& s[t] != '"')
		asto_bi(a, &i, s[t++], 1);
	a->size -= t - len;
	if (t > (len + PROG_NAME_LENGTH))
		leave(a, ": PROG_NAME_LENGTH EXCEEDED.\n", 0);
	if (s[t++] != '"')
		leave(a, ": SYNTAX ERROR AT COMMAND NAME_CMD_STRING.\n", 0);
	return (t += is_endline(a, s + t));
}

size_t	is_hcomment(t_asm *a, char *s)
{
	size_t	t;
	int		i;
	size_t	len;

	t = 0;
	if (!ft_strnequ(s, COMMENT_CMD_STRING, 8))
		return (0);
	if (a->comm++ == 1)
		leave(a, ": MULTIPLE COMMENT_CMD_STRING COMMAND.\n", 0);
	t = ft_strlen(COMMENT_CMD_STRING);
	while (s[t] == ' ' || s[t] == '\t' || s[t] == '\v')
		t += 1;
	if (s[t++] != '"')
		leave(a, ": SYNTAX ERROR AT COMMAND COMMENT_CMD_STRING.\n", 0);
	i = (PROG_NAME_LENGTH + 12);
	len = t;
	while (s[t] && t <= (len + COMMENT_LENGTH) \
		&& s[t] != '"')
		asto_bi(a, &i, s[t++], 1);
	a->size -= t - len;
	if (t > (len + COMMENT_LENGTH))
		leave(a, ": COMMENT_LENGTH EXCEEDED.\n", 0);
	if (s[t++] != '"')
		leave(a, ": SYNTAX ERROR AT COMMAND COMMENT_CMD_STRING.\n", 0);
	return (t += is_endline(a, s + t));
}

size_t	is_op(t_asm *a, char *s)
{
	size_t	t;
	size_t	i;

	t = 0;
	while (s[t] >= 'a' && s[t] <= 'z')
		t += 1;
	i = 0;
	while (i < 16)
	{
		if (ft_strnequ(s, a->op_tab[i].name, t) \
			&& t == ft_strlen(a->op_tab[i].name))
			return (i);
		i += 1;
	}
	return (16);
}

size_t	is_opline(t_asm *a, char *s)
{
	size_t	t;
	size_t	op;

	t = 0;
	while (ft_strchr(LABEL_CHARS, s[t]))
		t++;
	if (!t)
		return (0);
	if (s[t] == ':' && a->name == 1 && a->comm == 1)
	{
		get_labeldef(a, s, t++);
		return (t += is_endline(NULL, s + t));
	}
	if ((op = is_op(a, s)) == 16)
		leave(a, ": INVALID OPERATION.\n", t);
	if (a->name != 1 || a->comm != 1)
		leave(a, ": MISSING NAME_CMD_STRING OR COMMENT_CMD_STRING \
BEFORE FIRST INSTRUCTION.\n", t);
	return (t += check_args(a, s + t, op));
}

void	get_cor(t_asm *a)
{
	size_t	i;
	size_t	t;

	a->size = 0;
	i = 0;
	while (a->chp[i])
	{
		while (a->chp[i] == ' ' || a->chp[i] == '\t' || a->chp[i] == '\v')
			i += 1;
		if ((t = is_hname(a, a->chp + i)) > 0)
			i += t;
		else if ((t = is_hcomment(a, a->chp + i)) > 0)
			i += t;
		else if ((t = is_opline(a, a->chp + i)) > 0)
			i += t;
		else if ((t = is_endline(a, a->chp + i)) > 0)
			i += t;
		else
			leave(a, ": INVALID LINE.\n", 0);
	}
}
