/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 10:18:43 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/03 15:25:33 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void        arena_render(t_visu *v, t_parse *p)
{
    int     i;
    
	i = 0;
	while (i < p->nb_champ)
	{
		SDL_SetRenderDrawColor(v->renderer, 255, 255, 0, 255);
		SDL_RenderCopy(v->renderer, v->chp_vn[i], NULL, &v->chp_id[i]);
        SDL_SetRenderDrawColor(v->renderer, 255, 255, 0, 255);
		SDL_RenderCopy(v->renderer, v->chp_vs[i], NULL, &v->chp_cs[i]);
		i++;
	}
	i = 0;
	while (i < MEM_SIZE)
    {
		SDL_RenderCopy(v->renderer, v->arena_vs[i], NULL, &v->arena_pos[i]);
        i++;
    }
    i = 0;
    while (i < 3)
    {
        SDL_RenderCopy(v->renderer, v->process_vt[i], NULL, &v->process_tc[i]);
        SDL_RenderCopy(v->renderer, v->process_vn[i], NULL, &v->process_coo[i]);
        i++;  
    }
}

void        visu_render(t_visu *v, t_parse *p)
{
    SDL_SetRenderDrawColor(v->renderer, 0, 0, 0, 255);
	SDL_RenderClear(v->renderer);
	SDL_SetRenderDrawColor(v->renderer, 0, 255, 0, 255);
	SDL_RenderCopy(v->renderer, v->texture_title, NULL, &v->position);
	SDL_SetRenderDrawColor(v->renderer, 255, 255, 0, 255);
	SDL_RenderDrawRect(v->renderer, &v->process_id);
	SDL_SetRenderDrawColor(v->renderer, 255, 255, 0, 255);
	SDL_RenderDrawRect(v->renderer, &v->arena_rect);
	SDL_SetRenderDrawColor(v->renderer, 255, 255, 0, 255);
	SDL_RenderDrawRect(v->renderer, &v->process_rect);
    arena_render(v, p);
	SDL_RenderPresent(v->renderer);
	if (SDL_PollEvent(&v->event))
	{
		if (v->event.type == SDL_QUIT)
			v->isquit = 1;
		if (v->event.type == SDL_KEYUP)
			if (v->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				v->isquit = 1;
	}
}

void	texture_free(t_visu *v)
{
	int i;
	
	SDL_DestroyTexture(v->menu_vt);
	SDL_DestroyTexture(v->texture_title);
	i = 0;
	while (i < 4)
	{
		SDL_DestroyTexture(v->chp_vn[i]);
		SDL_DestroyTexture(v->chp_vs[i]);
		i++;
	}
	i = 0;
	while (i < MEM_SIZE)
	{
		SDL_DestroyTexture(v->arena_vs[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		SDL_DestroyTexture(v->process_vn[i]);
		SDL_DestroyTexture(v->process_vt[i]);
		i++;
	}
}

void	render_destroy(t_visu *v)
{
	SDL_DestroyRenderer(v->renderer);
	SDL_DestroyWindow(v->screen);
	TTF_Quit();
	Mix_FreeMusic(v->musique);
   	Mix_CloseAudio();
	SDL_Quit();
}