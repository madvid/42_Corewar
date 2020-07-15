/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:49:57 by yaye              #+#    #+#             */
/*   Updated: 2020/07/03 15:49:58 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include "op.h"

# define OP "abcdefghijklmnopqrstuvwxyz"
# define HEXA_BASE "0123456789abcdef"
# define COR_MAX MEM_SIZE / 6 * 8
/*
** >----------------------------- ASM STRUCTURES -----------------------------<
*/

/*typedef struct		s_labelcall
{
	char				*label;
	int					position;
	struct s_labelcall	*next;
}					t_labelcall;*/

/*typedef struct		s_labeldef
{
	char				*label;
	int					position;
	struct s_labeldef	*next;
}					t_labeldef;*/

typedef struct		s_op
{
	char				*name;
	size_t				n_arg;
	size_t				*type;
	int					nb;
	int					cycle;
	char				*descriptif;
	int					encoded;
	int					inconnu;
}					t_op;

typedef struct		s_asm
{
	t_op    op_tab = {"live", 1, {T_DIR}, 1, 10, "alive", 0, 0};
	int					name;			//set to 0 in get_champion() controler qu'il n'y a qu'une seule fois la commande .name
	int					comm;			//set to 0 in get_champion() controler qu'il n'y a qu'une seule fois la commande .comment
	char				*chp;			//malloc dans get_champion()
	char				cor[COR_MAX];	//possibilité de le set à taille max au lieu de malloc -- ft_memset() dans get_champion()
}					t_asm;

/*
** >-------------------------------- FUNCTIONS -------------------------------<
*/

#endif
