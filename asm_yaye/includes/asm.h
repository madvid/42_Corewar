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

# define NAME_SIZE 4096
# define COR_MAX (PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE + 16)

/*
** >----------------------------- ASM STRUCTURES -----------------------------<
*/

typedef struct		s_ope
{
	int					i_op;
	int					i_encod;
	size_t				encoded;
	size_t				p_encod;
	size_t				n_arg;
}					t_ope;

typedef struct		s_lb
{
	char				*lb;			//malloc
	size_t				byte_size;
	int					i_op;
	int					i_call;
	size_t				line;
	struct s_lb			*next;
}					t_lb;

typedef struct		s_asm
{
	t_op				*op_tab;
	char				*chp;			//malloc dans get_champion()
	char				cor[COR_MAX];	//possibilité de le set à taille max au lieu de malloc -- ft_memset() dans get_champion()
	int					i;				//indice du .cor
	int					size;			//Instruction Section Size
	t_lb				*ldef;			//malloc
	t_lb				*lcall;			//malloc
	int					name;			//set to 0 in get_champion() controler qu'il n'y a qu'une seule fois la commande .name
	int					comm;			//set to 0 in get_champion() controler qu'il n'y a qu'une seule fois la commande .comment
	size_t				line;
}					t_asm;

/*
** >-------------------------------- FUNCTIONS -------------------------------<
*/

void	ft_putnb(size_t n);
void	release(t_asm *a);
void	leave(t_asm *a, char *s, size_t col);
void	asto_bi(t_asm *a, int *i, int c, int bytes);
size_t	is_endline(t_asm *a, char *s);
size_t	is_opline(t_asm *a, char *s);
size_t	check_args(t_asm *a, char *s, size_t op);
void	get_labeldef(t_asm *a, char *s, size_t len);
size_t	get_labelcall(t_asm *a, char *s, size_t byte_size, t_ope *ope);
void	get_cor(t_asm *a);

#endif
