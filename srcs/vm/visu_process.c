/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 09:52:05 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/07 12:08:45 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_visu		init_process(t_visu *v)
{
	v->process_title[0] = TTF_RenderText_Blended(v->font_process,\
			"Cycle to die: ", v->color_title);
	if (!v->process_title[0])
		printf("Error creating text : %s\n", SDL_GetError());
	v->process_title[1] = TTF_RenderText_Blended(v->font_process,\
			"Nb_lives during this CTD: ", v->color_title);
	if (!v->process_title[1])
		printf("Error creating text : %s\n", SDL_GetError());
	v->process_title[2] = TTF_RenderText_Blended(v->font_process,\
			"NB of check before CTD: ", v->color_title);
	if (!v->process_title[2])
		printf("Error creating text : %s\n", SDL_GetError());
	v->process_title[3] = TTF_RenderText_Blended(v->font_process,\
			"Total nbr of lives: ", v->color_title);
	if (!v->process_title[3])
		printf("Error creating text : %s\n", SDL_GetError());
	v->process_title[4] = TTF_RenderText_Blended(v->font_process,\
			"Number of Cycle: ", v->color_title);
	if (!v->process_title[4])
		printf("Error creating text : %s\n", SDL_GetError());
	v->process_rect.x = 405;
	v->process_rect.y = 1080;
	v->process_rect.w = 2500 - 405;
	v->process_rect.h = 270;
	return (*v);
}

void		set_coo_process(t_visu *v, int i)
{
	if (i < 3)
	{
		v->process_tc[i].x = v->process_rect.x + 10;
		v->process_tc[i].y = v->process_rect.y + i * 100;
		v->process_tc[i].w = 300;
		v->process_tc[i].h = 100;
		v->process_coo[i].x = v->process_tc[i].x + 700;
		v->process_coo[i].y = v->process_tc[i].y;
		v->process_coo[i].w = 300;
		v->process_coo[i].h = 100;
	}
	else
	{
		v->process_tc[i].x = v->process_rect.x + 1200;
		v->process_tc[i].y = v->process_rect.y + (i % 3) * 100;
		v->process_tc[i].w = 300;
		v->process_tc[i].h = 100;
		v->process_coo[i].x = v->process_tc[i].x + 600;
		v->process_coo[i].y = v->process_tc[i].y;
		v->process_coo[i].w = 300;
		v->process_coo[i].h = 100;
	}
	
}

void		get_process_data(t_visu *v, t_cw *cw)
{
	v->process_name[0] = TTF_RenderText_Blended(v->font_process,\
			ft_itoa(cw->cycle_to_die), v->color_title);
	if (!v->process_name[0])
		printf("Error creating text : %s\n", SDL_GetError());
	v->process_name[1] = TTF_RenderText_Blended(v->font_process,\
			ft_itoa(cw->ctd_lives), v->color_title);
	if (!v->process_name[1])
		printf("Error creating text : %s\n", SDL_GetError());
	v->process_name[2] = TTF_RenderText_Blended(v->font_process,\
			ft_itoa(cw->i_check), v->color_title);
	if (!v->process_name[2])
		printf("Error creating text : %s\n", SDL_GetError());
	v->process_name[3] = TTF_RenderText_Blended(v->font_process,\
			ft_itoa(cw->tot_lives), v->color_title);
	if (!v->process_name[3])
		printf("Error creating text : %s\n", SDL_GetError());
	v->process_name[4] = TTF_RenderText_Blended(v->font_process,\
			ft_itoa(cw->i_cycle), v->color_title);
	if (!v->process_name[4])
		printf("Error creating text : %s\n", SDL_GetError());
}

void		process_to_texture(t_visu *v, int i)
{
	v->process_vt[i] = SDL_CreateTextureFromSurface(v->r,
			v->process_title[i]);
	if (!v->process_vt[i])
		printf("Error creating texture : %s\n", SDL_GetError());
	SDL_QueryTexture(v->process_vt[i], NULL, NULL, &v->process_tc[i].w,
			&v->process_tc[i].h);
	SDL_FreeSurface(v->process_title[i]);
	SDL_SetRenderDrawBlendMode(v->r, SDL_BLENDMODE_BLEND);
	v->process_vn[i] = SDL_CreateTextureFromSurface(v->r,
			v->process_name[i]);
	if (!v->process_vn[i])
		printf("Error creating texture : %s\n", SDL_GetError());
	SDL_QueryTexture(v->process_vn[i], NULL, NULL, &v->process_coo[i].w,
			&v->process_coo[i].h);
	SDL_FreeSurface(v->process_name[i]);
	SDL_SetRenderDrawBlendMode(v->r, SDL_BLENDMODE_BLEND);
}

void		load_process(t_visu *v, t_cw *cw)
{
	int		i;

	get_process_data(v, cw);
	i = 0;
	while (i < 5)
	{
		set_coo_process(v, i);
		process_to_texture(v, i);
		i++;
	}
}
