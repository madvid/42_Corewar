/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:52:37 by mdavid            #+#    #+#             */
/*   Updated: 2020/09/02 16:31:27 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H


/*
** --------------------------------------------------------------
** include de fichiers entête
** --------------------------------------------------------------
*/

/*
** fichiers entête externes à Corewar
*/
# include <stdbool.h>

/*
** fichiers entête internes à Corewar
*/
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "define_uint_linux.h"
# include "error_messages.h"

/*
** fichier entête du sujet corewar (ressources) + structure op
*/

# include "op_and_op_struct.h"

/*
** --------------------------------------------------------------
** Macros des auteurs, des structures et prototypes des fonctions
** --------------------------------------------------------------
*/

# define RELATIVE 10
# define DUMP_SIG FIN_DU_GAME

/*
** Inclusion des structures de la partie vm (parsing etc...)
*/

# include "corewar_struct.h"

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
void				tool_print_short_processors(t_cw *cw);								// a retirer
void				tool_print_short_champ_list(t_list *lst_champs);					// a retirer

/*
** Prototypes des fonctions du manager d'erreurs [vm_error_manager.c]
*/

int					vm_error_manager(int code_error, t_parse **p, t_cw **cw);
int					vm_init_parse_error(int code_error, t_parse **p);	// print error message if memory allocation issue at initialization
int					vm_init_cw_error(int cd_error, t_cw **cw);
void				ft_lst_fdel_champ(void *link);
void				ft_lst_fdel_proc(void *proc);

/*
** Prototypes des fonctions de parsing des arguments en STDIN
*/

int					vm_parsing(char **av, t_parse **p);
int					vm_init_parse(t_parse **p);
int					vm_create_champion(t_list **lst_champs, char *av, t_parse *p);
int 				is_valid_champ_filename(char* filename);
int					vm_options_flag(char **av, t_parse **p, int *i);
int					is_dump_option(char *arg, t_parse *p);
int					in_verbose_range(char *arg);
int		            is_valid_nb_champ(char *nb);
int		            id_number_chp_flag(t_parse **p, char **av, int *i);

/*
** Prototypes des fonctions de parsing des fichiers des champions
*/

int					vm_champ_parse(t_list **lst_champs, t_parse **p);
int					get_champ_magic_key(int fd);
char				*get_champ_name(int fd);
char				*get_champ_comment(int fd);
int					get_champ_l_bcode(int fd);
char				*get_champ_bcode(int fd, int l_bcode);
int					lst_sort_champion(t_list **champ);
int					lst_order_chp(t_list *chp1, t_list *chp2);
t_list				*reconstruct_champ_list(t_list **tab_champ, int nb_champ);
t_list				*get_champ_id(t_list **champ, int id);


/*
** Prototypes des fonctions [initialization et chargement] de l'arene et des cursors
*/

int					vm_cw_arena_init(t_cw **cw, t_parse **p);

/*
** Lancement et déroulement de corewar.
*/
void				vm_champion_introduction(t_list **lst_champs);
int					vm_execution(t_cw *cw);
void				vm_exec_init_pc(t_cw *cw);
int					procedural_loop(t_cw *cw);
void				new_attribut_proc(t_cw *cw, t_process *proc);
int					ctd_control(t_cw *cw);

bool				is_valid_encoding(u_int8_t opcode, u_int8_t encoding);
int					instruction_width(unsigned char encoding, t_op op_elem);
char				*champ_name_via_id(t_list *lst_champs, int id);

/*
** Fonctions outils concernant les opcode
*/
bool				opcode_no_encoding(u_int8_t opcode);

/*
** Fonctions outils concernant l'octet d'encodage
*/
int					get_nb_arg_b_encoding(u_int8_t encoding);
bool				is_valid_encoding(unsigned char opcode, unsigned char encoding);
bool				is_valid_reg(t_cw *cw, t_process *p);

/*
** Fonctions concernant le déroulement des processus au sein de la VM
*/
void				vm_proc_cycle(t_cw *cw);
int					vm_proc_perform_opcode(t_cw *cw, t_process *proc);
void				vm_proc_mv_proc_pos(t_cw *cw, t_process *proc);
int					vm_proc_get_lives(t_cw *cw);
void				vm_proc_set_lives(t_cw *cw, int set);
int					vm_proc_kill_not_living(t_cw *cw);
void				free_one_process(t_list **lst_proc, int id);
bool				vm_proc_only_one_standing(t_cw *cw);
int					declare_winner(t_cw *cw);

/*
** Fonctions pour effectuer les instructions asm dans l'arene
*/
int					op_alive(t_cw *cw, t_process *cur_proc);
int					op_load(t_cw *cw, t_process *cur_proc);
int					op_store(t_cw *cw, t_process *cur_proc);
int					op_addition(t_cw *cw, t_process *cur_proc);
int					op_soustraction(t_cw *cw, t_process *cur_proc);
int					op_and(t_cw *cw, t_process *cur_proc);
int					op_or(t_cw *cw, t_process *cur_proc);
int					op_xor(t_cw *cw, t_process *cur_proc);
int					op_zerojump(t_cw *cw, t_process *cur_proc);
int					op_load_index(t_cw *cw, t_process *cur_proc);
int					op_store_index(t_cw *cw, t_process *cur_proc);
int					op_fork(t_cw *cw, t_process *cur_proc);
int					op_long_load(t_cw *cw, t_process *cur_proc);
int					op_long_load_index(t_cw *cw, t_process *cur_proc);
int					op_long_fork(t_cw *cw, t_process *cur_proc);
int					op_aff(t_cw *cw, t_process *cur_proc);
int					fork_creation_process(t_cw *cw, t_process *cur_proc, int addr);
int					get_arg_value(t_cw *cw, t_process *cur_proc, int index, int type);
void				write_in_arena(t_cw *cw, t_process *p, int arg[3]);
void				write_in_reg(t_cw *cw, t_process *p, int arg[3]);


/*
** Fonctions pour la gestion des options de ./corewar
*/
int					dump_memory(char *arena);

/*
**<<<<<<<<<<<<<<<<<<<<<Bonus Functions>>>>>>>>>>>>>>>>>>>>
**
**<<<<<Verbosity>>>>>
*/

void				verbotab(t_cw *cw, t_process *p, t_arg a);
int		 			vprint_essentials(t_cw *cw, void *ptr, t_arg a,int flag);
void	 			vprint_lives(t_cw *cw, t_arg a);
void				vprint_cycle(t_cw *cw, int flag);
void	 			vprint_op(t_process *p, t_arg a);
void	 			vprint_deaths(t_cw *cw, t_process *ptr);
void	 			vprint_pcmv(t_cw *cw, t_process *p, t_arg a);
char				*args_to_str(t_arg a);
void				opcode_g(void *ptr, char *tmp, t_arg a);
void				opcode_v10(void *ptr, t_arg a);
void				opcode_v11(void *ptr, t_arg a);
void				opcode_v12(void *ptr, t_arg a);
void				opcode_v14(void *ptr, t_arg a);
void				op_arg_init(t_arg *arg, int type0, int type_select);
void				tool_print_t_arg(t_arg arg);

#endif
