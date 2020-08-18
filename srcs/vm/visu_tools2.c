/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:36:32 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/18 13:06:51 by armajchr         ###   ########.fr       */
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
	//vm_proc_get_lives(cw); <- augmentation de cw->tot_lives/ctd_lives pendant l'action alive, peut etre retiré donc.
	// if (cw->ctd_lives == 0 || !vm_proc_only_one_standing(cw))
	if (cw->ctd_lives == 0 || cw->process == NULL)
		stop_game = true;
	if (cw->i_check++ == MAX_CHECKS || cw->ctd_lives >= NBR_LIVE)
	{
		cw->cycle_to_die -= (int)CYCLE_DELTA;
		cw->i_check = (cw->i_check == MAX_CHECKS) ? 0 : cw->i_check;
		if (cw->options->v_lvl & 2)
		{
			vprint_cycle(cw, NULL, 1);
			// vprint_cycle(cw, NULL, 0);
		}
	}
	if (vm_proc_kill_not_living(cw) == 0 || cw->cycle_to_die <= 0)
		return (declare_winner(cw));
	vm_proc_set_lives(cw, 0);
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
