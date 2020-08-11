/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 10:48:49 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/11 14:17:47 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		init_window(t_visu *v)
{
	v->screen = NULL;
	v->r = NULL;
	v->angle = 0;
	v->menu_loop = 0;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("Error SDL Init\n");
	if (TTF_Init() < 0)
		printf("Error TTF Init\n");
	SDL_CreateWindowAndRenderer(2500, 1400,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &v->screen,
			&v->r);
}

t_visu		init_visu(t_visu *v)
{
	v->isquit = 0;
	v->color_title = (SDL_Color) {0, 209, 209, 255};
	v->color_id = (SDL_Color) { 255, 255, 0, 255};
	v->process_id.x = 0;
	v->process_id.y = 70;
	v->process_id.w = 400;
	v->process_id.h = 1280;
	v->text_title = TTF_RenderText_Blended(v->font_title, "Corewar",\
			v->color_title);
	if (!v->text_title)
		printf("Error creating text : %s\n", SDL_GetError());
	v->texture_title = SDL_CreateTextureFromSurface(v->r,
			v->text_title);
	if (!v->texture_title)
		printf("Error creating texture : %s\n", SDL_GetError());
	return (*v);
}

void		load_title(t_visu *v)
{
	v->position.x = 1200;
	v->position.y = 15;
	SDL_QueryTexture(v->texture_title, NULL, NULL, &v->position.w,
			&v->position.h);
	SDL_FreeSurface(v->text_title);
	SDL_SetRenderDrawBlendMode(v->r, SDL_BLENDMODE_BLEND);
}

void		load_visu(t_visu *v, t_cw *cw, t_parse *p)
{
	*v = init_visu(v);
	*v = init_arena(v);
	*v = init_id(v, cw);
	*v = init_process(v);
	*v = init_players(v, p);
	load_title(v);
	load_chp(v, cw);
	load_arena(v, cw);
	load_process(v, cw);
	load_players(v, p);
}

void		visualizer(t_cw *cw, t_parse *p)
{
	t_visu		v;
	static bool	stop_game;

	init_window(&v);
	music_launcher(&v);
	v = init_details(&v);
	v = init_menu(&v);
	load_menu(&v);
	vm_exec_init_pc(cw);
	cw->cycle_to_die = 200;
	while (stop_game == false && v.isquit == 0)
	{
		if (v.menu_loop == 0)
			v.angle = menu_move(&v, v.angle);
		else
			stop_game = main_exe(&v, cw, stop_game, p);
		if (v.isquit == 1)
			break ;
		v = visu_breaker(&v);
	}
	render_destroy(&v);
}
