/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:52:37 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/27 13:58:20 by mdavid           ###   ########.fr       */
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

#include <stdio.h> // <-- HAVE TO BE REMOVED AT THE END

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
** structure pour exploiter le fichier op.c
*/

typedef struct					s_op
{
	char				*name;
	size_t				n_arg;
	size_t				type[MAX_ARGS_NUMBER];
	size_t				code;
	size_t				cycle;
	char				*desc;
	size_t				encod;
	size_t				direct_size;
}								t_op;

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
	int				mem_pos;
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

typedef struct		s_process
{
	int				id;				// unique to each process
	bool			carry;			// flag carry= which can be changed by certain operations and which affects zjmp operation, initialised with value false.
	char			opcode;			// operation code, before the battle starts it is not initialised. use define and table of correspondance to stock the opcode read and to find the info in op_tab[17]
	int				n_lives;		// number of lives the process performed DURING THE CURRENT CYCLE_TO_DIE period, meaning that when cw->cycle_to_die becomes 0, value is reset to 0.
	int				last_live;		// nb of cycle in which current cursor performed operation live last time.
	int				wait_cycles;	// amount of cycles to wait before operation execution.
	void			*position;		// position address in memory
	int				jump;			// amount of bytes cursor must jump to get to the next operation
	void			*pc;			// program counter = register that load the next opcode address that will be executed for the current process
	char			**registers;	// 16 registers for a process/cursors of 4 bytes each.
	t_champ			*champ;
}					t_process;

typedef struct		s_corewar
{
	char			*arena;			// memory area where champion will fight until death
	int				*id_arena;		// memory area where id champion are placed on the arena to keep a track of which champion occuped which bytes.
	t_list			*process;		// "incarnation of the champion", part which will read & execute the champion code (~ish, not exactly)
	int				cycle_to_die;	// 
	int				tot_lives;		// If the number of lives performed by the processes reachs nb-lives, cycle_to_die is decreased by delta_cycle.
	int				n_champ;		// number of champions in the arena = to nb_champ of parse structure.
	int				champ_lives[4];	// Cumulated number of lives for each champion.
	int				i_check;		// Number of check to perform before cycle_to_die is decreased (no matter if nb_lives is reached or not)
}					t_cw;

/*
** Prototypes de fonctions temporaires, à retirer avant de push sur la vogsphere.
*/
void				tool_print_parsing(t_parse *p);										// a retirer
void				tool_print_champ(t_champ *champ);									// a retirer
void				tool_print_champ_list(t_list *lst_champs);							// a retirer
void				tool_print_arena(char *arena, size_t mem_size, t_parse *p);			// a retirer
void				tool_print_id_arena(int *id_arena, size_t mem_size, t_parse *p);	// a retirer
void				tool_print_processor(t_process *process, int nb);					// a retirer
void				tool_print_all_processors(t_list *processes);						// a retirer

/*
** Prototypes des fonctions du manager d'erreurs [vm_error_manager.c]
*/
int					vm_error_manager(int code_error, char **error);
int					vm_init_parse_error(int code_error, t_parse **p);	// print error message if memory allocation issue at initialization
int					vm_init_cw_error(int cd_error, t_cw **cw);

/*
** Prototypes des fonctions de parsing des arguments en STDIN
*/
int					vm_parsing(char **av, t_parse *p);
int					vm_init_parse(t_parse **p);
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
int					vm_cw_arena_init(t_cw **cw, t_parse **p);

/*
** Lancement et déroulement de corewar.
*/
void				vm_champion_introduction(t_list *lst_champs);
int					vm_execution(t_cw *cw);
void				vm_exec_init_pc(t_cw *cw);
bool				is_valid_encoding(unsigned char opcode, unsigned char encoding);
int					instruction_width(unsigned char encoding, size_t dir_s);

/*
** Fonctions outils concernant les opcode
*/
bool				is_opcode(char *arena, int pos);
int					arg_size_opcode_no_encode(u_int8_t opcode);
bool				opcode_no_encoding(u_int8_t opcode);
void				*addr_next_opcode(char *arena, int mem_pos);
void				perform_opcode(t_cw *cw, t_process *cur_proc);

/*
** Fonctions outils concernant l'octet d'encodage
*/
int					get_nb_arg_b_encoding(unsigned char encoding);
bool				is_valid_encoding(unsigned char opcode, unsigned char encoding);

/*
** Fonctions concernant le déroulement des processus au sein de la VM
*/
void				vm_proc_cycle(t_cw *cw);
void				vm_proc_perform_opcode(t_cw *cw);
void				vm_proc_mv_proc_pos(t_cw *cw);
int					vm_proc_get_lives(t_cw *cw);
void				vm_proc_set_lives(t_cw *cw, int set);
void				vm_proc_kill_not_living(t_cw *cw);
void				free_one_process(t_list **lst_proc, int id);
bool				vm_proc_only_one_standing(t_cw *cw);

/*
** Fonctions pour effectuer les instructions asm dans l'arene
*/
int					op_alive(t_cw *cw, t_process *cur_proc, t_op op_elem);
int					op_load(t_cw *cw, t_process *cur_proc, t_op op_elem);
int					op_store(t_cw *cw, t_process *cur_proc, t_op op_elem);
int					op_addition(t_cw *cw, t_process *cur_proc, t_op op_elem);
int					op_soustraction(t_cw *cw, t_process *cur_proc, t_op op_elem);
int					op_and(t_cw *cw, t_process *cur_proc, t_op op_elem);
int					op_or(t_cw *cw, t_process *cur_proc, t_op op_elem);
int					op_xor(t_cw *cw, t_process *cur_proc, t_op op_elem);
int					op_zerojump(t_cw *cw, t_process *cur_proc, t_op op_elem);
int					op_load_index(t_cw *cw, t_process *cur_proc, t_op op_elem);
int					op_store_index(t_cw *cw, t_process *cur_proc, t_op op_elem);
int					op_fork(t_cw *cw, t_process *cur_proc, t_op op_elem);
int					op_long_load(t_cw *cw, t_process *cur_proc, t_op op_elem);
int					op_long_load_index(t_cw *cw, t_process *cur_proc, t_op op_elem);
int					op_long_fork(t_cw *cw, t_process *cur_proc, t_op op_elem);
int					op_aff(t_cw *cw, t_process *cur_proc, t_op op_elem);

#endif