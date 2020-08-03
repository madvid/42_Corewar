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

t_visu	init_details(t_visu *v)
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
	v->color_arena = (SDL_Color) {255, 255, 255, 255}; //white
    v->chp_color = v->color_arena;
    v->color_chp[0] = (SDL_Color) {255, 0, 0, 255};  //red
    v->color_chp[1] = (SDL_Color) {142, 68, 173, 255}; //purple
    v->color_chp[2] = (SDL_Color) {36, 113, 163, 255}; //blue
    v->color_chp[3] = (SDL_Color) {255, 255, 0, 255}; //yellow
    v->color_process = (SDL_Color) {48, 204, 111, 255}; //light_green
	return (*v);
}

t_visu	init_visu(t_visu *v)
{
	v->isquit = 0;
	v->color_title = (SDL_Color) {0, 209, 209, 255};
	v->color_id = (SDL_Color) { 255, 255, 0, 255};
	v->process_id.x = 0;
	v->process_id.y = 70;
	v->process_id.w = 400;
	v->process_id.h = 1280;
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
	static bool	stop_game;

	init_window(&v);
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    	printf("%s", Mix_GetError());
	v.musique = Mix_LoadMUS("./Visu/8-bit-music-chiptune-reloaded.mp3");
	v = init_details(&v);
	v = init_menu(&v);
	load_menu(&v);
	vm_exec_init_pc(cw);
	cw->cycle_to_die = 1000; // to supress
	//Mix_PlayMusic(v.musique, -1);
	while (stop_game == false && v.isquit == 0)
	{
		if (v.menu_loop == 0)
			v.angle = menu_move(&v, v.angle);  
		else
		{
			cw->i_cycle = -1;
			while (++cw->i_cycle < cw->cycle_to_die && v.menu_loop != 0 && v.isquit == 0)
			{
				load_visu(&v, p, cw);	
				visu_render(&v, p);
				vm_proc_cycle(cw);
				vm_proc_perform_opcode(cw);
				vm_proc_mv_proc_pos(cw);
				printf("i_cycle = %d\n", cw->i_cycle);
				texture_free(&v);
			}
					// ICI ajouter une fonction qui va attribuer une valeur a cw->lives + retirer les processus qui n'ont pas live pendant cw->cycle_to_die cycle
			cw->tot_lives = vm_proc_get_lives(cw);
			vm_proc_kill_not_living(cw);
			if (cw->tot_lives == 0 || !vm_proc_only_one_standing(cw))
				stop_game = true;
			//break ; // to suppress;
			vm_proc_set_lives(cw, 0);
			if (cw->tot_lives >= NBR_LIVE)
				cw->cycle_to_die -= (int)CYCLE_DELTA;
		}
		if (SDL_PollEvent(&v.event))
	    {
		    if (v.event.type == SDL_QUIT)
			    v.isquit = 1;
			if (v.event.type == SDL_KEYUP)
			{
				if(v.event.key.keysym.scancode == SDL_SCANCODE_SPACE)
					v.menu_loop++;
				if (v.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					v.isquit = 1;
			}
		}
	} 
	render_destroy(&v);
}