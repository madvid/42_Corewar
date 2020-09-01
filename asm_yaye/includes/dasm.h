/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:36:25 by yaye              #+#    #+#             */
/*   Updated: 2020/08/31 15:36:26 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DASM_H
# define DASM_H
# include "libft.h"
# include "op.h"

# define NAME_SIZE 4096
# define CHP_SIZE 16384
# define COR_MAX (PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE + 16)

/*
** >----------------------------- ASM STRUCTURES -----------------------------<
*/

typedef struct		s_dasm
{
	t_op				*op_tab;
	char				chp[CHP_SIZE];
	char				cor[COR_MAX];
	size_t				i;
}					t_dasm;

/*
** >-------------------------------- FUNCTIONS -------------------------------<
*/

void	leave(t_dasm *a, char *s);
void	get_s(t_dasm *a);

#endif
