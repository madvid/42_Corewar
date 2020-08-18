/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:36:32 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/17 11:34:08 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			find_nbr_players(t_parse *p)
{
	t_list	*xplr;
	int		i;

	xplr = p->lst_champs;
	i = 0;
	while (xplr)
	{
		i++;
		xplr = xplr->next;
	}
	return (i);
}

bool		main_exe2(t_cw *cw, bool stop_game)
{
	vm_proc_get_lives(cw);
	vm_proc_kill_not_living(cw);
	if (cw->tot_lives == 0)
		stop_game = true;
	vm_proc_set_lives(cw, 0);
	if (cw->ctd_lives >= NBR_LIVE || cw->i_check++ == MAX_CHECKS)
	{
		cw->cycle_to_die -= (int)CYCLE_DELTA;
		cw->i_check = 0;
		if (cw->options->v_lvl & 2)
			vprint_cycle(cw, NULL, 1);
	}
	return (stop_game);
}

void		arena_texture(t_visu *v, int is_proc, int i)
{
	if (is_proc == 0)
		v->arena_txt[i] = TTF_RenderText_Blended(v->arena_font,\
				v->final, v->chp_color);
	ft_memdel((void**)&v->final);
	if (!v->arena_txt[i])
		printf("Error creating arena_txt : %s\n", SDL_GetError());
	v->arena_vs[i] = SDL_CreateTextureFromSurface(v->r,
			v->arena_txt[i]);
	if (!v->arena_vs[i])
		printf("Error creating arena_vs : %s\n", SDL_GetError());
	SDL_QueryTexture(v->arena_vs[i], NULL, NULL, &v->arena_pos[i].w,
			&v->arena_pos[i].h);
	SDL_FreeSurface(v->arena_txt[i]);
	SDL_SetRenderDrawBlendMode(v->r, SDL_BLENDMODE_BLEND);
}
