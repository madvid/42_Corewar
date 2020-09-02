/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:16:11 by mdavid            #+#    #+#             */
/*   Updated: 2020/09/01 19:21:40 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_STRUCT_H
# define COREWAR_STRUCT_H

/*
** fichiers entête externes à Corewar
*/
# include <stdbool.h>

/*
** fichiers entête internes à Corewar
*/
# include "../libft/include/libft.h"

/*
** fichier entête du sujet corewar (ressources) + structure op
*/

# include "op_and_op_struct.h"

/*
** Définition des structures de la partie vm (parsing etc...)
*/

typedef struct		s_options
{
	bool			dump;
	int				dump_cycle;
	bool			n;
	bool			aff;
	bool			sdl;
	bool			music;
	bool			verbose;
	int				v_p;
	u_int8_t		v_lvl;
}					t_options;

typedef struct		s_arg
{
	int				type[3];
	int				arg[3];
	int				widht;
}					t_arg;

typedef struct		s_champ
{
	int				id;
	char			*champ_file;
	char			*name;
	char			*comment;
	int				l_bytecode;
	char			*bytecode;
	int				mem_pos;
}					t_champ;

typedef struct		s_parse
{
	int				nb_champ;
	int				id_champ;
	int				*id_available;
	t_options		*options;
	t_list			*lst_champs;
	char			**error;
}					t_parse;

typedef struct		s_process
{
	int				id;				// unique to each process
	bool			carry;			// flag carry= which can be changed by certain operations and which affects zjmp operation, initialised with value false.
	int				opcode;			// operation code, before the battle starts it is not initialised. use define and table of correspondance to stock the opcode read and to find the info in op_tab[17]
	int				n_lives;		// number of lives the process performed DURING THE CURRENT CYCLE_TO_DIE period, meaning that when cw->cycle_to_die becomes 0, value is reset to 0.
	int				last_live;		// cycle number at which the process did an alive for the last time.
	int				wait_cycles;	// amount of cycles to wait before operation execution.
	int				i;				// i is the index of the process in the cw->arena
	int				pc;				// program counter = register that load the next opcode address that will be executed for the current process
	int				*registers;		// 16 registers for a process/cursors of 4 bytes each.
	t_champ			*champ;
}					t_process;

typedef struct		s_corewar
{
	t_op			*op_tab;
	char			*arena;			// memory area where champion will fight until death
	int				*id_arena;		// memory area where id champion are placed on the arena to keep a track of which champion occuped which bytes.id des champs a chaque case.
	t_list			*process;		// "incarnation of the champion", part which will read & execute the champion code (~ish, not exactly)
	int				n_champ;		// number of champions in the arena = to nb_champ of parse structure.
	int				champ_lives[4];	// Cumulated number of lives for each champion.
	t_list			*lst_champs;
	int				i_cycle;
	int				cycle_to_die;	// 
	int				tot_lives;		// total number of alive performed since the beginning of the battle.
	int				ctd_lives;		// number of alives performed during the last CTD period.
	int				i_check;		// Number of check to perform before cycle_to_die is decreased (no matter if nb_lives is reached or not)
	int				tot_cycle;
	int				last_champ;
	t_options		*options;			// struct with options
}					t_cw;

#endif