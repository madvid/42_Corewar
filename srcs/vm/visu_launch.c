/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 12:25:52 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/21 15:13:49 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vm.h"

t_visu	init_visu(t_visu *v)
{
	v->isquit = 0;
	v->color_title = (SDL_Color) {0, 209, 209, 255};
	v->color_id = (SDL_Color) { 255, 255, 0, 255};
	v->process_id.x = 0;
	v->process_id.y = 0;
	v->process_id.w = 400;
	v->process_id.h = 1350;
	v->font_title = TTF_OpenFont("./visu/THANK YOU KOBE.ttf", 50);
	if (!v->font_title)
		printf("Error creating font : %s\n", SDL_GetError());
	v->text_title = TTF_RenderText_Blended(v->font_title, "Corewar", v->color_title);
	if (!v->text_title)
		printf("Error creating text : %s\n", SDL_GetError());
	v->texture_title = SDL_CreateTextureFromSurface(v->renderer,
			v->text_title);
	if (!v->texture_title)
		printf("Error creating texture : %s\n", SDL_GetError());
	return (*v);
}

void	load_title(t_visu *v)
{
	v->position.x = 1200;
	v->position.y = 15;
	SDL_QueryTexture(v->texture_title, NULL, NULL, &v->position.w,
			&v->position.h);
	SDL_FreeSurface(v->text_title);
	SDL_SetRenderDrawBlendMode(v->renderer, SDL_BLENDMODE_BLEND);
}

void	load_visu(t_visu *v, t_parse *p, t_cw *cw)
{			
	*v = init_visu(v);
	*v = init_arena(v);
	*v = init_id(v, p);
	*v = init_process(v);
	load_title(v);
	load_chp(v, p);
	load_arena(v, cw, p);
	load_process(v, cw);
}

void	init_window(t_visu *v)
{
	v->screen = NULL;
	v->renderer = NULL;
	v->angle = 0;
	v->menu_loop = 0;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("Error SDL Init\n");
	if (TTF_Init() < 0)
		printf("Error TTF Init\n");
	SDL_CreateWindowAndRenderer(2500, 1400,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &v->screen,
			&v->renderer);
}

void     visualizer(t_parse *p, t_cw *cw)
{
	t_visu		v;
	int			i_cycle;
	static bool	stop_game;
	int			first;

	init_window(&v);
	v = init_menu(&v);
	load_menu(&v);
	vm_exec_init_pc(cw);
	cw->cycle_to_die = 100; // to supress
	first = 0;
	while (stop_game == false && v.isquit == 0)
	{
		if (SDL_PollEvent(&v.event))
	    {
		    if (v.event.type == SDL_QUIT)
			    v.isquit = 1;
			if (v.event.type == SDL_KEYUP)
				if(v.event.key.keysym.scancode == SDL_SCANCODE_SPACE)
					v.menu_loop++;
			if (v.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				v.isquit = 1;
		}
		if (v.menu_loop == 0)
			v.angle = menu_move(&v, v.angle);
		else
		{
			i_cycle = -1;
			while (++i_cycle < cw->cycle_to_die && v.menu_loop != 0)
			{
				load_visu(&v, p, cw);
				visu_render(&v, p);
				printf(">>> i_cycle = %d\n", i_cycle);
				vm_proc_cycle(cw);
				vm_proc_perform_opcode(cw);
				vm_proc_mv_proc_pos(cw);

			}
			// ICI ajouter une fonction qui va attribuer une valeur a cw->lives + retirer les processus qui n'ont pas live pendant cw->cycle_to_die cycle
			cw->tot_lives = vm_proc_get_lives(cw);
			vm_proc_kill_not_living(cw);
			if (cw->tot_lives == 0 || !vm_proc_only_one_standing(cw))
				stop_game = true;
			break ; // to suppress;
			vm_proc_set_lives(cw, 0);
			if (cw->tot_lives >= NBR_LIVE)
				cw->cycle_to_die -= (int)CYCLE_DELTA;
		}
	}
	render_destroy(&v);
}