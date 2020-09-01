/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:39:55 by armajchr          #+#    #+#             */
/*   Updated: 2020/09/01 19:42:10 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visu.h"

t_visu		init_menu(t_visu *v)
{
	v->flip = (SDL_FLIP_NONE);
	v->menu_color = (SDL_Color) {0, 209, 209, 255};
	v->font_menu = TTF_OpenFont("./visu/THANK YOU KOBE.ttf", 400);
	if (!v->font_menu)
		printf("Error creating font : %s\n", SDL_GetError());
	v->menu_txt = TTF_RenderText_Blended(v->font_menu,\
			"Corewar", v->menu_color);
	if (!v->menu_txt)
		printf("Error creating menu_text : %s\n", SDL_GetError());
	v->menu_vt = SDL_CreateTextureFromSurface(v->r, v->menu_txt);
	if (!v->menu_vt)
		printf("Error creating menu_vt : %s\n", SDL_GetError());
	return (*v);
}

void		load_menu(t_visu *v)
{
	v->menu_pos.x = 600;
	v->menu_pos.y = 500;
	SDL_QueryTexture(v->menu_vt, NULL, NULL, &v->menu_pos.w,\
			&v->menu_pos.h);
	SDL_FreeSurface(v->menu_txt);
	SDL_SetRenderDrawBlendMode(v->r, SDL_BLENDMODE_BLEND);
	v->center.x = v->menu_pos.w / 2;
	v->center.y = v->menu_pos.h / 2;
}

void		menu_move(t_visu *v)
{
	if (v->angle < 0)
		v->angle = 360;
	if (v->angle > 360)
		v->angle = 0;
	v->angle++;
	init_menu(v);
	load_menu(v);
	SDL_RenderClear(v->r);
	SDL_RenderCopyEx(v->r, v->menu_vt, NULL, &v->menu_pos,\
			v->angle, &v->center, v->flip);
	SDL_RenderPresent(v->r);
	SDL_Delay(10);
}
