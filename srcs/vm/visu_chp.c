/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_chp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 10:30:51 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/04 10:52:20 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_visu		init_id(t_visu *v, t_parse *p)
{
	int		i;
	t_list	*xplr;

	i = 0;
	xplr = p->lst_champs;
	v->chp_n = 1;
	while (xplr && v->chp_n != ((t_champ*)(xplr->cnt))->id)
		xplr = xplr->next;
	while (i < p->nb_champ)
	{
		v->chp_id[i].x = 20;
		v->chp_id[i].y = v->process_id.y + (i * 350);
		v->chp_id[i].w = 400;
		v->chp_id[i].h = 150;
		v->chp_name[i] = TTF_RenderText_Blended(v->font_p,\
			((t_champ*)(xplr->cnt))->name, v->color_chp[i]);
		if (!v->chp_name[i])
			printf("Error creating text : %s\n", SDL_GetError());
		v->chp_vn[i] = SDL_CreateTextureFromSurface(v->r, v->chp_name[i]);
		if (!v->chp_vn[i])
			printf("Error creating texture : %s\n", SDL_GetError());
		v->chp_cs[i].x = v->chp_id[i].x;
		v->chp_cs[i].y = v->chp_id[i].y + 40;
		v->chp_cs[i].w = 400;
		v->chp_cs[i].h = 150;
		v->chp_size[i] = TTF_RenderText_Blended(v->font_p,\
				ft_itoa(((t_champ*)(xplr->cnt))->l_bytecode), v->color_chp[i]);
		if (!v->chp_size[i])
			printf("Error creating text : %s\n", SDL_GetError());
		v->chp_vs[i] = SDL_CreateTextureFromSurface(v->r, v->chp_size[i]);
		if (!v->chp_vs[i])
			printf("Error creating texture : %s\n", SDL_GetError());
		i++;
		xplr = p->lst_champs;
		while (xplr && i != ((t_champ*)(xplr->cnt))->id)
			xplr = xplr->next;
	}
	return (*v);
}

void		load_chp(t_visu *v, t_parse *p)
{
	int		i;

	i = 0;
	while (i < p->nb_champ)
	{
		SDL_QueryTexture(v->chp_vn[i], NULL, NULL, &v->chp_id[i].w,\
				&v->chp_id[i].h);
		SDL_FreeSurface(v->chp_name[i]);
		SDL_SetRenderDrawBlendMode(v->r, SDL_BLENDMODE_BLEND);
		SDL_QueryTexture(v->chp_vs[i], NULL, NULL, &v->chp_cs[i].w,\
				&v->chp_cs[i].h);
		SDL_FreeSurface(v->chp_size[i]);
		SDL_SetRenderDrawBlendMode(v->r, SDL_BLENDMODE_BLEND);
		i++;
	}
}
