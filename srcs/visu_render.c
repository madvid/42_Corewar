/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 10:18:43 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/23 12:41:47 by armajchr         ###   ########.fr       */
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
}

void	render_destroy(t_visu *v)
{
	SDL_DestroyRenderer(v->renderer);
	SDL_DestroyWindow(v->screen);
	TTF_Quit();
	SDL_Quit();
}