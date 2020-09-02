/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_chp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 10:30:51 by armajchr          #+#    #+#             */
/*   Updated: 2020/09/02 16:17:02 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visu.h"

void		fill_coo_proc(t_visu *v, int i)
{
	v->chp_id[i].x = 20;
	v->chp_id[i].y = v->process_id.y + (i * 100);
	v->chp_id[i].w = 400;
	v->chp_id[i].h = 150;
	v->chp_cs[i].x = v->chp_id[i].x;
	v->chp_cs[i].y = v->chp_id[i].y + 40;
	v->chp_cs[i].w = 400;
	v->chp_cs[i].h = 150;
}

void		fill_proc_name(t_visu *v, t_list *xplr, int i)
{
	char		*dst;
	char		*tmp;
	char		*tmp2;
	extern t_op	op_tab[17];

	if (((t_process*)(xplr->cnt))->opcode <= 0 \
			|| ((t_process*)(xplr->cnt))->opcode >= 17)
		tmp2 = ft_strjoin("no op", ":                  ");
	else
		tmp2 = ft_strjoin(op_tab[((t_process*)(xplr->cnt))->opcode - 1].name, \
				":                  ");
	tmp = ft_itoa(((t_process*)(xplr->cnt))->opcode);
	dst = ft_strjoin(tmp2, tmp);
	ft_memdel((void**)&tmp2);
	ft_memdel((void**)&tmp);
	tmp = ft_itoa(((t_process*)(xplr->cnt))->last_live);
	tmp2 = ft_strjoin(dst, "     Last Live:       ");
	dst = ft_strjoin(tmp2, tmp);
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&tmp2);
	v->chp_name[i] = TTF_RenderText_Blended(v->font_p,\
			dst, v->color_process);
	if (!v->chp_name[i])
		printf("Error creating chp_name : %s\n", SDL_GetError());
	ft_memdel((void**)&dst);
}

void		fill_proc_texture(t_visu *v, t_list *xplr, int i)
{
	char		*dst;
	char		*tmp;
	extern t_op	op_tab[17];

	v->chp_vn[i] = SDL_CreateTextureFromSurface(v->r, v->chp_name[i]);
	if (!v->chp_vn[i])
		printf("Error creating texture chp_vn : %s\n", SDL_GetError());
	tmp = ft_itoa(((t_process*)(xplr->cnt))->wait_cycles);
	dst = ft_strjoin("Wait cycle until process:     ", \
			tmp);
	ft_memdel((void**)&tmp);
	v->chp_size[i] = TTF_RenderText_Blended(v->font_p,\
			dst, v->color_process);
	if (!v->chp_size[i])
		printf("Error creating chp_size : %s\n", SDL_GetError());
	v->chp_vs[i] = SDL_CreateTextureFromSurface(v->r, v->chp_size[i]);
	if (!v->chp_vs[i])
		printf("Error creating chp_vs : %s\n", SDL_GetError());
	ft_memdel((void**)&dst);
}

t_visu		init_id(t_visu *v, t_cw *cw)
{
	int			i;
	int			j;
	t_list		*xplr;

	i = 0;
	j = find_nbr_proc(cw);
	xplr = cw->process;
	while (xplr && i < j)
	{
		fill_coo_proc(v, i);
		fill_proc_name(v, xplr, i);
		fill_proc_texture(v, xplr, i);
		i++;
		xplr = xplr->next;
	}
	while (i < 13)
	{
		v->chp_name[i] = NULL;
		v->chp_vs[i] = NULL;
		i++;
	}
	return (*v);
}

void		load_chp(t_visu *v, t_cw *cw)
{
	int		i;
	int		j;

	i = 0;
	j = find_nbr_proc(cw);
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
