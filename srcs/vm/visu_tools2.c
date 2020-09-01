/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:36:32 by armajchr          #+#    #+#             */
/*   Updated: 2020/09/01 19:43:28 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visu.h"

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
	if (cw->ctd_lives == 0 || cw->process == NULL)
		stop_game = true;
	ctd_control(cw);
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
		printf("Error creating arena_txt[%d] : %s\n", i, SDL_GetError());
	v->arena_vs[i] = SDL_CreateTextureFromSurface(v->r,
			v->arena_txt[i]);
	if (!v->arena_vs[i])
		printf("Error creating arena_vs : %s\n", SDL_GetError());
	SDL_QueryTexture(v->arena_vs[i], NULL, NULL, &v->arena_pos[i].w,
			&v->arena_pos[i].h);
	SDL_FreeSurface(v->arena_txt[i]);
	SDL_SetRenderDrawBlendMode(v->r, SDL_BLENDMODE_BLEND);
}

void		get_process_data2(t_visu *v, t_cw *cw)
{
	char	*tmp;

	tmp = ft_itoa(cw->tot_lives);
	v->process_name[3] = TTF_RenderText_Blended(v->font_process,\
			tmp, v->color_title);
	ft_memdel((void**)&tmp);
	tmp = ft_itoa(cw->i_cycle);
	v->process_name[4] = TTF_RenderText_Blended(v->font_process,\
			tmp, v->color_title);
	ft_memdel((void**)&tmp);
	tmp = ft_itoa(cw->tot_cycle);
	v->process_name[5] = TTF_RenderText_Blended(v->font_process,\
			tmp, v->color_title);
	ft_memdel((void**)&tmp);
}

void		final_render_destroy(t_visu *v)
{
	if (v->menu_loop == 0)
	{
		SDL_DestroyTexture(v->menu_vt);
		SDL_DestroyTexture(v->texture_title);
	}
	else
		texture_free(v);
}
