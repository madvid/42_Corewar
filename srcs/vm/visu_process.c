/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 09:52:05 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/30 11:10:35 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vm.h"

t_visu      init_process(t_visu *v)
{
    v->font_process = TTF_OpenFont("./visu/Raleway-Black.ttf", 50);
	if (!v->font_title)
		printf("Error creating font : %s\n", SDL_GetError());
    v->process_title[0] = TTF_RenderText_Blended(v->font_process, "Cycle to die: ", v->color_title);
	if (!v->process_title[0])
		printf("Error creating text : %s\n", SDL_GetError());
    v->process_title[1] = TTF_RenderText_Blended(v->font_process, "Nb_lives: ", v->color_title);
	if (!v->process_title[1])
		printf("Error creating text : %s\n", SDL_GetError());
    v->process_title[2] = TTF_RenderText_Blended(v->font_process, "i_cycle: ", v->color_title);
	if (!v->process_title[2])
		printf("Error creating text : %s\n", SDL_GetError());
    v->process_rect.x = 400;
    v->process_rect.y = 1075;
    v->process_rect.w = 2500 - 400;
    v->process_rect.h = 275;
    return (*v);
}

void    set_coo_process(t_visu *v, int i)
{
    v->process_tc[i].x = v->process_rect.x + 10;
    v->process_tc[i].y = v->process_rect.y + i * 100;
    v->process_tc[i].w = 300;
    v->process_tc[i].h = 100 ;
    v->process_coo[i].x = v->process_tc[i].x + 600;
    v->process_coo[i].y = v->process_tc[i].y;
    v->process_coo[i].w = 300;
    v->process_coo[i].h = 100;
}

void    get_process_data(t_visu *v, t_cw *cw)
{
    v->process_name[0] = TTF_RenderText_Blended(v->font_process, ft_itoa(cw->cycle_to_die), v->color_title);
	if (!v->process_name[0])
		printf("Error creating text : %s\n", SDL_GetError());
    v->process_name[1] = TTF_RenderText_Blended(v->font_process, ft_itoa(cw->tot_lives), v->color_title);
	if (!v->process_name[1])
		printf("Error creating text : %s\n", SDL_GetError());
    v->process_name[2] = TTF_RenderText_Blended(v->font_process, ft_itoa(cw->i_cycle), v->color_title);
	if (!v->process_name[2])
		printf("Error creating text : %s\n", SDL_GetError());
}

void    process_to_texture(t_visu *v, int i)
{
	v->process_vt[i] = SDL_CreateTextureFromSurface(v->renderer,
		v->process_title[i]);
	if (!v->process_vt[i])
		printf("Error creating texture : %s\n", SDL_GetError());
    SDL_QueryTexture(v->process_vt[i], NULL, NULL, &v->process_tc[i].w,
	    &v->process_tc[i].h);
	SDL_FreeSurface(v->process_title[i]);
	SDL_SetRenderDrawBlendMode(v->renderer, SDL_BLENDMODE_BLEND);
    v->process_vn[i] = SDL_CreateTextureFromSurface(v->renderer,
		v->process_name[i]);
	if (!v->process_vn[i])
		printf("Error creating texture : %s\n", SDL_GetError());
    SDL_QueryTexture(v->process_vn[i], NULL, NULL, &v->process_coo[i].w,
	    &v->process_coo[i].h);
	SDL_FreeSurface(v->process_name[i]);
	SDL_SetRenderDrawBlendMode(v->renderer, SDL_BLENDMODE_BLEND);
}

void    load_process(t_visu *v, t_cw *cw)
{
    int i;

    get_process_data(v, cw);
    i = 0;
    while (i < 3)
    {
        set_coo_process(v, i);
        process_to_texture(v, i);
        i++;
    }
}