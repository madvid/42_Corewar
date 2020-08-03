/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:39:55 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/03 14:41:19 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_visu  init_menu(t_visu *v)
{
    v->flip = (SDL_FLIP_NONE);
    v->menu_color = (SDL_Color) {0, 209, 209, 255};
    v->font_menu = TTF_OpenFont("./visu/THANK YOU KOBE.ttf", 400);
    if (!v->font_menu)
		printf("Error creating font : %s\n", SDL_GetError());
	v->menu_txt = TTF_RenderText_Blended(v->font_menu, "Corewar", v->menu_color);
	if (!v->menu_txt)
		printf("Error creating text : %s\n", SDL_GetError());
	v->menu_vt = SDL_CreateTextureFromSurface(v->renderer,
			v->menu_txt);
	if (!v->menu_vt)
		printf("Error creating texture : %s\n", SDL_GetError());
    return (*v);
}

void    load_menu(t_visu *v)
{
    v->menu_pos.x = 600;
	v->menu_pos.y = 500;
	SDL_QueryTexture(v->menu_vt, NULL, NULL, &v->menu_pos.w,
			&v->menu_pos.h);
	SDL_FreeSurface(v->menu_txt);
	SDL_SetRenderDrawBlendMode(v->renderer, SDL_BLENDMODE_BLEND);
    v->center.x = v->menu_pos.w / 2;
    v->center.y = v->menu_pos.h / 2;
}

double    menu_move(t_visu *v, double angle)
{
    if (angle < 0)
        angle = 360;
    if (angle > 360)
        angle = 0;
    angle++;
    SDL_SetRenderDrawColor(v->renderer, 0, 0, 0, 255);
    SDL_RenderClear(v->renderer);
    SDL_RenderCopyEx(v->renderer, v->menu_vt, NULL, &v->menu_pos, angle, &v->center, v->flip);
    SDL_RenderPresent(v->renderer);
    SDL_Delay(20);
    return (angle);
}