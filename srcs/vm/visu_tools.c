/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 09:43:18 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/24 18:15:20 by mdavid           ###   ########.fr       */
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
	v->color_chp[2] = (SDL_Color) {255, 255, 0, 255};
	v->color_chp[3] = (SDL_Color) {36, 113, 163, 255};
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

void		music_launcher(t_visu *v, t_cw *cw)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,\
		MIX_DEFAULT_CHANNELS, 1024) == -1)
		printf("%s", Mix_GetError());
	v->musique =\
		Mix_LoadMUS("./Visu/8-bit-music-chiptune-reloaded(1).mp3");
	(cw->options->music == true) ? Mix_PlayMusic(v->musique, -1) : 0;
}

int			find_nbr_proc(t_cw *cw)
{
	int		j;
	t_list	*xplr;

	j = 0;
	xplr = cw->process;
	while (xplr)
	{
		j++;
		xplr = xplr->next;
	}
	if (j > 13)
		j = 13;
	return (j);
}

bool		main_exe(t_visu *v, t_cw *cw, bool stop_game, t_parse *p)
{
	int		code_error;
	t_list		*xplr;
	t_process	*proc;

	code_error = 0;
	cw->i_cycle = 0;
	cw->ctd_lives = 0;
	while (++cw->i_cycle < cw->cycle_to_die && v->menu_loop != 0\
			&& v->isquit == 0)
	{
		xplr = cw->process;
		while (xplr)
		{
			proc = (t_process*)(xplr->cnt);
			load_visu(v, cw, p);
			visu_render(v);
			new_attribut_proc(cw, proc);
			proc->wait_cycles--;
			if ((code_error = vm_proc_perform_opcode(cw, proc)) != 0)
				return (code_error);
			xplr = xplr->next;
		}
		cw->tot_cycle++;
		texture_free(v);
	}
	stop_game = main_exe2(cw, stop_game);
	return (stop_game);
}
