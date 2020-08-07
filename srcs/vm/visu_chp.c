/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_chp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 10:30:51 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/07 14:38:14 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_visu		init_id(t_visu *v, t_cw *cw)
{
	int		i;
	int		j;
	t_list	*xplr;
	extern t_op	op_tab[17];
	char	*dst;

	i = 0;
	xplr = cw->process;
	j = 0;
	while (xplr)
	{
		j++;
		ft_printf("j = %d\n", j);
		xplr = xplr->next;
	}
	xplr = cw->process;
	if (j > 20)
		j = 20;
	while (xplr && i < j)
	{
		v->chp_id[i].x = 20;
		v->chp_id[i].y = v->process_id.y + (i * 100);
		v->chp_id[i].w = 400;
		v->chp_id[i].h = 150;
		dst = ft_strjoin(op_tab[((t_process*)(xplr->cnt))->opcode - 1].name,":                  ");
		dst = ft_strjoin(dst, ft_itoa(((t_process*)(xplr->cnt))->opcode));
		v->chp_name[i] = TTF_RenderText_Blended(v->font_p,\
			dst, v->color_process);
		free(dst);
		if (!v->chp_name[i])
			printf("Error creating text : %s\n", SDL_GetError());
		v->chp_vn[i] = SDL_CreateTextureFromSurface(v->r, v->chp_name[i]);
		if (!v->chp_vn[i])
			printf("Error creating texture : %s\n", SDL_GetError());
		v->chp_cs[i].x = v->chp_id[i].x;
		v->chp_cs[i].y = v->chp_id[i].y + 40;
		v->chp_cs[i].w = 400;
		v->chp_cs[i].h = 150;
		dst = ft_strjoin("Wait cycle until process:     ", ft_itoa(((t_process*)(xplr->cnt))->wait_cycles));
		v->chp_size[i] = TTF_RenderText_Blended(v->font_p,\
			dst, v->color_process);
		free(dst);
		if (!v->chp_size[i])
			printf("Error creating text : %s\n", SDL_GetError());
		v->chp_vs[i] = SDL_CreateTextureFromSurface(v->r, v->chp_size[i]);
		if (!v->chp_vs[i])
			printf("Error creating texture : %s\n", SDL_GetError());
		i++;
		xplr = xplr->next;
	}
	return (*v);
}

void		load_chp(t_visu *v, t_cw *cw)
{
	int		i;
	int		j;
	t_list	*xplr;
	
	j = 0;
	xplr = cw->process;
	while (xplr)
	{
		j++;
		xplr = xplr->next;
	}
	if (j > 20)
		j = 20;
	i = 0;
	while (i < j)
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
