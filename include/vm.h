/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:52:37 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/16 00:54:05 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

/*
** --------------------------------------------------------------
** include de fichiers entête 'externe'
** --------------------------------------------------------------
*/
//#include <sys/types.h>
#include <stdbool.h>

#include <stdio.h> // <-- have to be removed at the end

/*
** [Put some explanations]
*/
# include "../libft/include/libft.h"
#include "error_messages.h"

/*
** fichier entête du sujet corewar (ressources)
*/
#include "op.h"

/*
** --------------------------------------------------------------
** Macros des auteurs, des structures et prototypes des fonctions
** --------------------------------------------------------------
*/

/*
** Définition des structures de la partie vm (parsing etc...)
*/

typedef struct		s_options
{
	bool			dump;
	ssize_t			nbr_cycle;
	bool			n;
}					t_options;

typedef struct		s_champ
{
	int				id;
	char			*champ_file;
	char			*name;
	char			*comment;
	int				l_bytecode;
	char			*bytecode;
}					t_champ;

typedef struct		s_parse
{
	int				nb_champ;
	int				id_champ;
	int				*id_table;
	t_options		*options;
	t_list			*lst_champs;
	char			**error;
}					t_parse;

typedef struct		s_cursor
{
	int				id; // unique
	bool			carry; // flag which can be changed by certain operations and which affects zjmp operation, initialised with value false.
	int				opcode; // operation code, before the battle starts it is not initialised. use define and table of correspondance
	int				last_live; // nb of cycle in which current cursor performed operation live last time.
	int				wait_cycles; // amount of cycles to wait before operation execution.
	int				position; // address in memory
	int				jump; // amount of bytes cursor must jump to get to the next operation
	int				*registries; // [REG_NUMBER] - registries of current cursor
}					t_cursor;

typedef struct		s_corewar
{
	char			*arena;
	t_list			*cursors;
}					t_cw;

/*
** Prototypes de fonctions temporaires, à retirer avant de push sur la vogsphere.
*/
void				vm_print_parsing(t_parse *p); //a retirer
void				vm_print_champ_list(t_list *lst_champs); //a retirer
void				vm_print_arena(char *arena, size_t mem_size); // a retirer

/*
** Prototypes des fonctions de parsing des arguments en STDIN
*/
int					vm_parsing(char **av, t_parse *p);
int					vm_init_parse(t_parse **p);
int					vm_init_parse_error(int code_error, t_parse **p); // print error message if memory allocation issue at initialization
int					vm_error_manager(int code_error, char **error);
int					vm_create_champion(t_list **lst_champs, char *av, t_parse *p);
int 				is_valid_champ_filename(char* filename);

/*
** Prototypes des fonctions de parsing des fichiers des champions
*/
int					vm_champ_parse(t_list **lst_champs, char **error);
int					get_champ_magic_key(int fd);
char				*get_champ_name(int fd);
char				*get_champ_comment(int fd);
int					get_champ_l_bcode(int fd);
char				*get_champ_bcode(int fd, int l_bcode);

/*
** Prototypes des fonctions [initialization et chargement] de l'arene et des cursors
*/
int					vm_cw_arena_init(t_cw **cw, t_parse *p);
int					vm_init_cw_error(int cd_error, t_parse **cw); 

#endif