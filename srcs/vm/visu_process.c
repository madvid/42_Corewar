/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 09:52:05 by armajchr          #+#    #+#             */
/*   Updated: 2020/09/04 11:50:01 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visu.h"

t_visu		init_process(t_visu *v)
{
	v->process_title[0] = TTF_RenderText_Blended(v->font_process,\
			"Cycle to die: ", v->color_title);
	v->process_title[1] = TTF_RenderText_Blended(v->font_process,\
			"Nb_lives during this CTD: ", v->color_title);
	v->process_title[2] = TTF_RenderText_Blended(v->font_process,\
			"Speed [1-501]: ", v->color_title);
	v->process_title[3] = TTF_RenderText_Blended(v->font_process,\
			"Total nbr process: ", v->color_title);
	v->process_title[4] = TTF_RenderText_Blended(v->font_process,\
			"Cycle in CTD: ", v->color_title);
	v->process_title[5] = TTF_RenderText_Blended(v->font_process,\
			"Cycle: ", v->color_title);
	if (!v->process_title[0] || !v->process_title[1] || !v->process_title[2] \
		|| !v->process_title[3] || !v->process_title[4] || !v->process_title[5])
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
	char	*tmp;

	tmp = ft_itoa(cw->cycle_to_die);
	v->process_name[0] = TTF_RenderText_Blended(v->font_process,\
			tmp, v->color_title);
	ft_memdel((void**)&tmp);
	tmp = ft_itoa(cw->ctd_lives);
	v->process_name[1] = TTF_RenderText_Blended(v->font_process,\
			tmp, v->color_title);
	ft_memdel((void**)&tmp);
	tmp = ft_itoa(v->cycle_sec);
	v->process_name[2] = TTF_RenderText_Blended(v->font_process,\
			tmp, v->color_title);
	ft_memdel((void**)&tmp);
	get_process_data2(v, cw);
	if (!v->process_name[0] || !v->process_name[1] || !v->process_name[2] \
		|| !v->process_name[3] || !v->process_name[4] || !v->process_name[5])
		printf("Error creating process_name : %s\n", SDL_GetError());
}

void		process_to_texture(t_visu *v, int i)
{
	v->process_vt[i] = SDL_CreateTextureFromSurface(v->r,
			v->process_title[i]);
	if (!v->process_vt[i])
		printf("Error creating process_vt : %s\n", SDL_GetError());
	SDL_QueryTexture(v->process_vt[i], NULL, NULL, &v->process_tc[i].w,
			&v->process_tc[i].h);
	SDL_FreeSurface(v->process_title[i]);
	SDL_SetRenderDrawBlendMode(v->r, SDL_BLENDMODE_BLEND);
	v->process_vn[i] = SDL_CreateTextureFromSurface(v->r,
			v->process_name[i]);
	if (!v->process_vn[i])
		printf("Error creating process_vn : %s\n", SDL_GetError());
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
	while (i < 6)
	{
		set_coo_process(v, i);
		process_to_texture(v, i);
		i++;
	}
}
