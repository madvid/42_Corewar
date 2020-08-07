/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 09:43:18 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/07 14:12:02 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_visu		init_details(t_visu *v)
{
	v->font_title = TTF_OpenFont("./visu/THANK YOU KOBE.ttf", 50);
	if (!v->font_title)
		printf("Error creating font : %s\n", SDL_GetError());
	v->font_p = TTF_OpenFont("./visu/Roboto-Black.ttf", 20);
	if (!v->font_p)
		printf("Error creating font : %s\n", SDL_GetError());
	v->font_process = TTF_OpenFont("./visu/Raleway-Black.ttf", 50);
	if (!v->font_title)
		printf("Error creating font : %s\n", SDL_GetError());
	v->arena_font = TTF_OpenFont("./Visu/digital-7.regular.ttf", 15);
	if (!v->arena_font)
		printf("Error creating font : %s\n", SDL_GetError());
	v->color_arena = (SDL_Color) {255, 255, 255, 255};
	v->chp_color = v->color_arena;
	v->color_chp[0] = (SDL_Color) {255, 0, 0, 255};
	v->color_chp[1] = (SDL_Color) {142, 68, 173, 255};
	v->color_chp[2] = (SDL_Color) {36, 113, 163, 255};
	v->color_chp[3] = (SDL_Color) {255, 255, 0, 255};
	v->color_process = (SDL_Color) {48, 204, 111, 255};
	return (*v);
}

t_visu		visu_breaker(t_visu *v)
{
	if (SDL_PollEvent(&v->event))
	{
		if (v->event.type == SDL_QUIT)
			v->isquit = 1;
		if (v->event.type == SDL_KEYUP)
		{
			if (v->event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				v->menu_loop++;
			if (v->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				v->isquit = 1;
		}
	}
	return (*v);
}

void		music_launcher(t_visu *v)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,\
				MIX_DEFAULT_CHANNELS, 1024) == -1)
		printf("%s", Mix_GetError());
	v->musique =\
				Mix_LoadMUS("./Visu/8-bit-music-chiptune-reloaded(1).mp3");
	Mix_PlayMusic(v->musique, -1);
}

void		main_exe(t_visu *v, t_cw *cw, bool stop_game)
{	
	int		code_error;

	cw->i_cycle = -1;
	while (++cw->i_cycle < cw->cycle_to_die && v->menu_loop != 0\
			&& v->isquit == 0)
	{
		load_visu(v, cw);
		visu_render(v);
		if (cw->options.dump && cw->i_cycle == cw->options.dump_cycle)
			v->isquit = 1;
		if (cw->options.v_lvl & 2 && cw->i_cycle != 0)
			vprint_cycle(cw, cw, 1);
		vm_proc_cycle(cw);
		if ((code_error = vm_proc_perform_opcode(cw)) != 0)
			v->isquit = 1;
		vm_proc_mv_proc_pos(cw);
		texture_free(v);
	}
	vm_proc_get_lives(cw);
	vm_proc_kill_not_living(cw);
	if (cw->tot_lives == 0 || !vm_proc_only_one_standing(cw))
		stop_game = true;
	vm_proc_set_lives(cw, 0);
	if (cw->ctd_lives >= NBR_LIVE || cw->i_check++ == MAX_CHECKS)
	{
		cw->cycle_to_die -= (int)CYCLE_DELTA;
		cw->i_check = 0;
	}
}
