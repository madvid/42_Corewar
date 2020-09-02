/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 00:10:11 by mdavid            #+#    #+#             */
/*   Updated: 2020/09/02 17:32:48 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

/*
** fichiers entête externes pour visu
*/

# include <math.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_timer.h>
# include <SDL2_image/SDL_image.h>
# include <SDL2_ttf/SDL_ttf.h>
# include <SDL2_mixer/SDL_mixer.h>

# include "op_and_op_struct.h"

/*
** Inclusion des structures de la partie vm (parsing etc...)
*/

# include "corewar_struct.h"

typedef struct		s_visu
{
	SDL_Window		*screen;
	SDL_Renderer	*r;
	int				isquit;
	SDL_Event		event;
	Mix_Music		*musique;
/*
**Menu data
*/
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
	SDL_Rect		chp_id[13];	//Rect for champion info
	TTF_Font		*font_p;
	SDL_Surface		*chp_name[13];
	SDL_Texture		*chp_vn[13];
	SDL_Rect		chp_cs[13];
	SDL_Surface		*chp_size[13];
	SDL_Texture		*chp_vs[13];

/*
**Arena data
*/
	SDL_Color		color_arena;
	SDL_Color		color_process;
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
	SDL_Rect		process_coo[6];
	SDL_Rect		process_tc[6];
	SDL_Surface		*process_name[6];
	SDL_Surface		*process_title[6];
	SDL_Texture		*process_vn[6];
	SDL_Texture		*process_vt[6];

/*
**players data
*/
	int				tot_players;
	SDL_Rect		players_coo[4];
	SDL_Rect		pid_coo[4];
	SDL_Surface		*players_name[4];
	SDL_Texture		*players_vn[4];
	SDL_Surface		*pid_name[4];
	SDL_Texture		*pid_vn[4];
/*
**Render data
*/
	int				i;

}					t_visu;

/*
**<<<<<Visualizer functions>>>>>
**
**<<<<<Window functions>>>>>
*/

void				init_window(t_visu *v);
t_visu				init_visu(t_visu *v);
void				load_title(t_visu *v);
int					visualizer(t_cw *cw, t_parse *p);
void				menu_move(t_visu *v);
void				load_menu(t_visu *v);
t_visu				init_menu(t_visu *v);
void				load_visu(t_visu *v, t_cw *cw, t_parse *p);

/*
**<<<<<Process functions>>>>>
*/
t_visu				init_id(t_visu *v, t_cw *cw);
void				load_chp(t_visu *v, t_cw *cw);
void				fill_coo_proc(t_visu *v, int i);
void				fill_proc_name(t_visu *v, t_list *xplr, int i);
void				fill_proc_texture(t_visu *v, t_list *xplr, int i);

/*
**<<<<<Arena functions>>>>>
*/

t_visu				init_arena(t_visu *v);
void				load_arena(t_visu *v, t_cw *cw);

/*
**<<<<<Render functions>>>>>
*/

void				visu_render(t_visu *v);
void				render_destroy(t_visu *v);
void				render_destroy(t_visu *v);
void				texture_free(t_visu *v);

/*
**<<<<<Cycle info functions>>>>>
*/

t_visu				init_process(t_visu *v);
void				load_process(t_visu *v, t_cw *cw);
void				get_process_data2(t_visu *v, t_cw *cw);

/*
**Players functions
*/

t_visu				init_players(t_visu *v, t_parse *p);
void				load_players(t_visu *v, t_parse *p);

/*
**<<<<<Tools>>>>>
*/

bool				main_exe(t_visu *v, t_cw *cw, bool stop_game, t_parse *p);
bool				main_exe2(t_cw *cw, bool stop_game);
void				music_launcher(t_visu *v, t_cw *cw);
t_visu				visu_breaker(t_visu *v);
t_visu				visu_breaker2(t_visu *v);
t_visu				init_details(t_visu *v);
int					find_nbr_proc(t_cw *cw);
int					find_nbr_players(t_parse *p);
void				arena_texture(t_visu *v, int is_proc, int i);
void				final_render_destroy(t_visu *v);
char				*ft_itoa_base2(unsigned long long nb, char *base);

#endif