/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 09:54:08 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/14 14:27:13 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		fill_coo_players(t_visu *v, int i)
{
	if (i <= 1)
	{
		v->players_coo[i].x = 200 + (i * 600);
		v->players_coo[i].y = 20;
		v->players_coo[i].w = 500;
		v->players_coo[i].h = 50;
		v->pid_coo[i].x = v->players_coo[i].x - 30;
		v->pid_coo[i].y = 20;
		v->pid_coo[i].w = 30;
		v->pid_coo[i].h = 25;
	}
	else
	{
		v->players_coo[i].x = 1600 + ((i % 3) * 300);
		v->players_coo[i].y = 20;
		v->players_coo[i].w = 500;
		v->players_coo[i].h = 50;
		v->pid_coo[i].x = v->players_coo[i].x - 30;
		v->pid_coo[i].y = 20;
		v->pid_coo[i].w = 30;
		v->pid_coo[i].h = 25;
	}
}

void		fill_players_name(t_visu *v, t_list *xplr, int i)
{
	char	*dst;
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(((t_champ*)(xplr->cnt))->id);
	tmp2 = ft_strjoin("P", tmp);
	dst = ft_strjoin(tmp2, ": ");
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&tmp2);
	v->pid_name[i] = TTF_RenderText_Blended(v->font_p,\
			dst, v->color_chp[((t_champ*)(xplr->cnt))->id - 1]);
	if (!v->pid_name[i])
		printf("Error creating pid->name : %s\n", SDL_GetError());
	v->players_name[i] = TTF_RenderText_Blended(v->font_p,\
			((t_champ*)(xplr->cnt))->name,\
			v->color_chp[((t_champ*)(xplr->cnt))->id - 1]);
	if (!v->players_name[i])
		printf("Error creating players_name : %s\n", SDL_GetError());
	ft_memdel((void**)&dst);
}

void		fill_players_texture(t_visu *v, int i)
{
	v->pid_vn[i] = SDL_CreateTextureFromSurface(v->r, v->pid_name[i]);
	if (!v->pid_vn[i])
		printf("Error creating texture : %s\n", SDL_GetError());
	v->players_vn[i] = SDL_CreateTextureFromSurface(v->r, v->players_name[i]);
	if (!v->players_vn[i])
		printf("Error creating texture : %s\n", SDL_GetError());
}

t_visu		init_players(t_visu *v, t_parse *p)
{
	t_list	*xplr;
	int		i;

	xplr = p->lst_champs;
	i = -1;
	while (xplr && ++i < v->tot_players)
	{
		fill_coo_players(v, i);
		fill_players_name(v, xplr, i);
		fill_players_texture(v, i);
		xplr = xplr->next;
	}
	while (++i < 4)
	{
		v->players_name[i] = NULL;
		v->players_vn[i] = NULL;
	}
	return (*v);
}

void		load_players(t_visu *v, t_parse *p)
{
	int		i;

	i = -1;
	v->tot_players = find_nbr_players(p);
	while (++i < v->tot_players)
	{
		SDL_QueryTexture(v->players_vn[i], NULL, NULL, &v->players_coo[i].w,\
				&v->players_coo[i].h);
		SDL_FreeSurface(v->players_name[i]);
		SDL_SetRenderDrawBlendMode(v->r, SDL_BLENDMODE_ADD);
	}
}
