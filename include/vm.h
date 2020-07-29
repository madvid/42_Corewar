/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:52:37 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/23 16:40:33 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_timer.h>
# include <SDL2_image/SDL_image.h>
# include <SDL2_ttf/SDL_ttf.h>
# include <SDL2_mixer/SDL_mixer.h>

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
// direct_size == 0 => 4 - (0 * 2) octets pour l’argument direct
// direct_size == 1 => 4 - (1 * 2) octets pour l’argument direct

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
	int				id;				// unique
	bool			carry;			// flag carry= which can be changed by certain operations and which affects zjmp operation, initialised with value false.
	char			opcode;			// operation code, before the battle starts it is not initialised. use define and table of correspondance
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
	t_list			*process;		// "incarnation of the champion", part which will read & execute the champion code (~ish, not exactly)
	int				cycle_to_die;	// 
	int				nb_lives;		// If the number of lives performed by the processes reachs nb-lives, cycle_to_die is decreased by delta_cycle.
	int				delta_cycle;
	int				inter_check;	// Number of check to perform before cycle_to_die is decreased (no matter if nb_lives is reached or not)
}					t_cw;

/*
**v
*/

typedef struct		s_visu
{
	SDL_Window		*screen;
	SDL_Renderer	*renderer;
	int				isquit;
	SDL_Event		event;
	SDL_RendererFlip	flip;
	TTF_Font		*font_menu;
	SDL_Rect		menu_pos;
	TTF_Font		*menu_font;
	SDL_Surface		*menu_txt;
	SDL_Texture		*menu_vt;
	SDL_Color		menu_color;
	SDL_Point		center;
	int				menu_loop;
	double			angle;
/*
**Title data
*/
	TTF_Font		*font_title;
	SDL_Surface		*text_title;		//window title;
	SDL_Texture		*texture_title;	
	SDL_Rect		position;		//Coo for title rect
	SDL_Color		color_title;
/*
**Chp data
*/
	SDL_Color		color_chp[4];
    SDL_Color		chp_color;
	SDL_Rect		chp_id[4];	//Rect for champion info
	SDL_Rect		chp_info[36];
	TTF_Font		*font_p;
	SDL_Surface		*chp_name[4];
	SDL_Texture		*chp_vn[4];
	SDL_Rect		chp_cs[4];
	SDL_Surface		*chp_size[4];
	SDL_Texture		*chp_vs[4];

/*
**Arena data
*/
	SDL_Color		color_arena;
	TTF_Font		*arena_font;
	SDL_Rect		arena_rect;
	SDL_Rect		arena_pos[MEM_SIZE];
	SDL_Surface		*arena_txt[MEM_SIZE];
	SDL_Texture		*arena_vs[MEM_SIZE];
	char			*dst;   //prep arena in SDL(malloc);
	char 			*final; //arena in SDL(malloc);
	int				count;  //go to next line in arena;
	int				chp_n; //champion id for color;
/*
**process data
*/
	SDL_Color		color_id;
	TTF_Font		*font_process;
	SDL_Rect		process_id;  //Rect for process id info
	SDL_Rect		process_rect;
	SDL_Rect		process_coo[3];
	SDL_Rect		process_tc[3];
	SDL_Surface		*process_name[3];
	SDL_Surface		*process_title[3];
	SDL_Texture		*process_vn[3];
	SDL_Texture		*process_vt[3];

}					t_visu;
/*
** Prototypes de fonctions temporaires, à retirer avant de push sur la vogsphere.
*/
void				tool_print_parsing(t_parse *p);								// a retirer
void				tool_print_champ(t_champ *champ);							// a retirer
void				tool_print_champ_list(t_list *lst_champs);					// a retirer
void				tool_print_arena(char *arena, size_t mem_size, t_parse *p);	// a retirer
void				tool_print_processor(t_process *process, int nb);			// a retirer
void				tool_print_all_processors(t_list *processes);				// a retirer

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
** Lancement du corewar.
*/
void				vm_champion_introduction(t_list *lst_champs);
int					vm_execution(t_cw *cw);
void				get_next_opcode(char *arena, int mem_pos);

/*
**------------------Bonus functions------------------
*/

/*
**Window functions
*/
void				init_window(t_visu *v, t_parse *p, t_cw *cw);
t_visu				init_visu(t_visu *v);
void				load_title(t_visu *v);
void     			visualizer(t_parse *p, t_cw *cw);
double    			menu_move(t_visu *v, double angle);
void    			load_menu(t_visu *v);
t_visu  			init_menu(t_visu *v);
/*
**Champions functions
*/
t_visu				init_id(t_visu *v, t_parse *p);
void				load_chp(t_visu *v, t_parse *p);
/*
**Arena functions
*/
t_visu				init_arena(t_visu *v);
void      			load_arena(t_visu *v, t_cw *cw, t_parse *p);
t_list				*get_chp_id(t_list *xplr, t_visu *v, t_parse *p, int i);
void				get_items_cnt(t_visu *v, t_cw *cw, int i);
void        		get_arena_texture(t_visu *v, int i);
/*
**Render functions
*/
void				visu_render(t_visu *v, t_parse *p);
void				arena_render(t_visu *v, t_parse *p);
void				render_destroy(t_visu *v);
void				render_destroy(t_visu *v);
/*
**Process info functions
*/
t_visu      		init_process(t_visu *v);
void				load_process(t_visu *v, t_cw *cw);
void				set_coo_process(t_visu *v, int i);
void				get_process_data(t_visu *v, t_cw *cw);
void				process_to_texture(t_visu *v, int i);
/*
**Tools
*/
char				*ft_itoa_base2(unsigned long long nb, char *base);
#endif