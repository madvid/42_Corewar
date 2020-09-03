/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 10:18:43 by armajchr          #+#    #+#             */
/*   Updated: 2020/09/04 11:44:51 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visu.h"

void		arena_render(t_visu *v)
{
	v->i = -1;
	while (++v->i < 13)
	{
		SDL_SetRenderDrawColor(v->r, 255, 255, 0, 255);
		SDL_RenderCopy(v->r, v->chp_vn[v->i], NULL, &v->chp_id[v->i]);
		SDL_SetRenderDrawColor(v->r, 255, 255, 0, 255);
		SDL_RenderCopy(v->r, v->chp_vs[v->i], NULL, &v->chp_cs[v->i]);
		SDL_DestroyTexture(v->chp_vn[v->i]);
		SDL_DestroyTexture(v->chp_vs[v->i]);
	}
	v->i = -1;
	while (++v->i < MEM_SIZE)
		SDL_RenderCopy(v->r, v->arena_vs[v->i], NULL, &v->arena_pos[v->i]);
	v->i = -1;
	while (++v->i < 6)
	{
		SDL_RenderCopy(v->r, v->process_vt[v->i], NULL, &v->process_tc[v->i]);
		SDL_RenderCopy(v->r, v->process_vn[v->i], NULL, &v->process_coo[v->i]);
	}
	v->i = -1;
	while (++v->i < v->tot_players)
	{
		SDL_RenderCopy(v->r, v->players_vn[v->i], NULL, &v->players_coo[v->i]);
		SDL_RenderCopy(v->r, v->pid_vn[v->i], NULL, &v->pid_coo[v->i]);
	}
}

t_visu		visu_breaker2(t_visu *v)
{
	if (SDL_PollEvent(&v->event))
	{
		if (v->event.type == SDL_QUIT)
			v->isquit = 1;
		if (v->event.type == SDL_KEYUP)
			if (v->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				v->isquit = 1;
		if (v->event.type == SDL_KEYUP)
		{
			if (v->event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				if (SDL_WaitEvent(&v->event))
					if (v->event.type == SDL_KEYDOWN)
						if (v->event.key.keysym.scancode == SDL_SCANCODE_R)
							return (*v);
			}
			if (v->event.key.keysym.scancode == SDL_SCANCODE_KP_PLUS \
				&& v->cycle_sec <= 500)
				v->cycle_sec += 10;
			if (v->event.key.keysym.scancode == SDL_SCANCODE_KP_MINUS \
				&& v->cycle_sec > 10)
				v->cycle_sec -= 10;
		}
	}
	return (*v);
}

void		visu_render(t_visu *v)
{
	SDL_SetRenderDrawColor(v->r, 0, 0, 0, 255);
	SDL_RenderClear(v->r);
	SDL_SetRenderDrawColor(v->r, 0, 255, 0, 255);
	SDL_RenderCopy(v->r, v->texture_title, NULL, &v->position);
	SDL_SetRenderDrawColor(v->r, 255, 255, 0, 255);
	SDL_RenderDrawRect(v->r, &v->process_id);
	SDL_SetRenderDrawColor(v->r, 255, 255, 0, 255);
	SDL_RenderDrawRect(v->r, &v->arena_rect);
	SDL_SetRenderDrawColor(v->r, 255, 255, 0, 255);
	SDL_RenderDrawRect(v->r, &v->process_rect);
	arena_render(v);
	SDL_RenderPresent(v->r);
	*v = visu_breaker2(v);
}

void		texture_free(t_visu *v)
{
	SDL_DestroyTexture(v->menu_vt);
	SDL_DestroyTexture(v->texture_title);
	v->i = -1;
	while (++v->i < 13)
	{
		SDL_DestroyTexture(v->chp_vn[v->i]);
		SDL_DestroyTexture(v->chp_vs[v->i]);
	}
	v->i = -1;
	while (++v->i < MEM_SIZE)
		SDL_DestroyTexture(v->arena_vs[v->i]);
	v->i = -1;
	while (++v->i < 6)
	{
		SDL_DestroyTexture(v->process_vn[v->i]);
		SDL_DestroyTexture(v->process_vt[v->i]);
	}
	v->i = -1;
	while (++v->i < v->tot_players)
	{
		SDL_DestroyTexture(v->players_vn[v->i]);
		SDL_DestroyTexture(v->pid_vn[v->i]);
	}
}

void		render_destroy(t_visu *v)
{
	SDL_DestroyRenderer(v->r);
	SDL_DestroyWindow(v->screen);
	TTF_Quit();
	Mix_FreeMusic(v->musique);
	Mix_CloseAudio();
	SDL_Quit();
}
