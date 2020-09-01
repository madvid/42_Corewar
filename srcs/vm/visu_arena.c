/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 09:40:12 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/21 16:22:20 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**Initialisation of arena Rect coord, arena and champions colors, champions id
**and setup of the var for \n in v->window
*/

t_visu		init_arena(t_visu *v)
{
	v->arena_rect.x = 405;
	v->arena_rect.y = 70;
	v->arena_rect.w = 2500 - 405;
	v->arena_rect.h = 1400 - 400;
	v->count = 0;
	v->chp_n = 1;
	return (*v);
}

/*
**Getting every items of arena coord, and writting '0' if needed
*/

void		get_arena_coo(t_visu *v, int i)
{
	v->arena_pos[i].x = (i > 0) ? v->arena_pos[i - 1].x + 15 :\
		v->arena_rect.x + 100;
	v->arena_pos[i].x = (i % 128 == 0) ? v->arena_rect.x + 100 :\
		v->arena_pos[i - 1].x + 15;
	v->arena_pos[i].y = v->arena_rect.y + (v->count * 30);
	v->arena_pos[i].w = 30;
	v->arena_pos[i].h = 30;
}

void		get_items_cnt(t_visu *v, t_cw *cw, int i)
{
	size_t	j;
	int		k;

	get_arena_coo(v, i);
	if (((int)cw->arena[i] & 255) < 16)
	{
		v->dst = ft_itoa_base2((int)cw->arena[i] & 255, "0123456789abcdef");
		if (!(v->final = (char*)malloc(sizeof(char) * ft_strlen(v->dst) + 1)))
			return ;
		v->final[0] = '0';
		j = -1;
		k = 1;
		while (++j < ft_strlen(v->dst))
		{
			v->final[k] = v->dst[j];
			k++;
		}
		ft_memdel((void**)&v->dst);
	}
	else
		v->final = ft_itoa_base2((int)cw->arena[i] & 255, "0123456789abcdef");
}

/*
**getting the texture for every items for final visualisation.
*/

void		get_arena_texture(t_visu *v, int i, t_cw *cw)
{
	t_list	*xplr;
	int		is_proc;

	xplr = cw->process;
	is_proc = 0;
	while (xplr)
	{
		if (i == ((t_process*)xplr->cnt)->i)
		{
			v->arena_txt[i] = TTF_RenderText_Blended(v->arena_font,\
					v->final, v->color_process);
			ft_memdel((void**)&v->final);
			is_proc++;
			break ;
		}
		xplr = xplr->next;
	}
	arena_texture(v, is_proc, i);
}

/*
**Loop for setting the arena rect
*/

void		load_arena(t_visu *v, t_cw *cw)
{
	int		i;

	i = 0;
	v->count = 0;
	while (i < MEM_SIZE)
	{
		if (cw->id_arena[i] == 0)
			v->chp_color = v->color_arena;
		else
			v->chp_color = v->color_chp[cw->id_arena[i] - 1];
		if (i % 128 == 0)
			v->count++;
		get_items_cnt(v, cw, i);
		get_arena_texture(v, i, cw);
		i++;
	}
}
