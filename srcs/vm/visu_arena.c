/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 09:40:12 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/30 11:05:43 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vm.h"

/*
**Initialisation of arena Rect coord, arena and champions colors, champions id
**and setup of the var for \n in v->window
*/

t_visu      init_arena(t_visu *v)
{
    v->arena_font = TTF_OpenFont("./Visu/digital-7.regular.ttf", 15);
    if (!v->arena_font)
		printf("Error creating font : %s\n", SDL_GetError());
    v->arena_rect.x = 400;
    v->arena_rect.y = 75;
    v->arena_rect.w = 2500 - 400;
    v->arena_rect.h = 1400 - 400;
    v->color_arena = (SDL_Color) {255, 255, 255, 255}; //white
    v->chp_color = v->color_arena;
    v->color_chp[0] = (SDL_Color) {255, 0, 0, 255};  //red
    v->color_chp[1] = (SDL_Color) {0, 255, 0, 255}; //green
    v->color_chp[2] = (SDL_Color) {0, 0, 255, 255}; //blue
    v->color_chp[3] = (SDL_Color) {255, 255, 0, 255}; //yellow
    v->color_process = (SDL_Color) {148, 0, 211, 200}; //light_gray
    v->count = 0;
    v->chp_n = 1;
    return (*v);
}

/*
**Searching in t_champ for champion's id to setup the right color in arena
**and champion's id loop
*/

t_list      *get_chp_id(t_list *xplr, t_visu *v, t_parse *p, int i)
{
    if (i == ((t_champ*)(xplr->cnt))->mem_pos + ((t_champ*)(xplr->cnt))->l_bytecode)
    {
        v->chp_n++;
        if (v->chp_n == p->nb_champ + 1)
            v->chp_n = 1;
        xplr = p->lst_champs;
        while(v->chp_n != ((t_champ*)(xplr->cnt))->id && xplr)
            xplr = xplr->next;
        v->chp_color = v->color_arena;
    }
    return (xplr);
}

/*
**Getting every items of arena coord, and writting '0' if needed
*/

void        get_items_cnt(t_visu *v, t_cw *cw, int i)
{
    size_t      j;
    int         k;

    v->arena_pos[i].x = (i > 0) ? v->arena_pos[i - 1].x + 15 : v->arena_rect.x + 10;
    v->arena_pos[i].x = (i % 138 == 0) ? v->arena_rect.x + 10 : v->arena_pos[i - 1].x + 15;
    v->arena_pos[i].y = v->arena_rect.y + (v->count * 30);
    v->arena_pos[i].w = 30;
    v->arena_pos[i].h = 30;
    if (((int)cw->arena[i] & 255) < 16)
    {
        v->dst = ft_itoa_base2((int)cw->arena[i] & 255, "0123456789abcdef");
        if (!(v->final = (char*)malloc(sizeof(char) * ft_strlen(v->dst) + 2)))
            return ;
        v->final[0] = '0';
        j = 0;
        k = 1;
        while (j < ft_strlen(v->dst))
        {
            v->final[k] = v->dst[j];
            j++;
            k++;
        }
    }
    else
        v->final = ft_itoa_base2((int)cw->arena[i] & 255, "0123456789abcdef");
}

/*
** getting the texture for every items for final visualisation.
*/

void        get_arena_texture(t_visu *v, int i, t_cw *cw)
{
    t_list  *xplr;
    int     is_proc;

    xplr = cw->process;
    is_proc = 0;
    while (xplr)
    {
        if (i == ((t_process*)xplr->cnt)->position - (void*)(cw->arena))
        {
            v->arena_txt[i] = TTF_RenderText_Blended(v->arena_font, v->final, v->color_process);
            is_proc++;
        }
        xplr = xplr->next;
    }
    if (is_proc == 0)
        v->arena_txt[i] = TTF_RenderText_Blended(v->arena_font, v->final, v->chp_color);
	if (!v->arena_txt[i])
		printf("Error creating text : %s\n", SDL_GetError());
	v->arena_vs[i] = SDL_CreateTextureFromSurface(v->renderer,
		v->arena_txt[i]);
	if (!v->arena_vs[i])
		printf("Error creating texture : %s\n", SDL_GetError());
    SDL_QueryTexture(v->arena_vs[i], NULL, NULL, &v->arena_pos[i].w,
	&v->arena_pos[i].h);
	SDL_FreeSurface(v->arena_txt[i]);
	SDL_SetRenderDrawBlendMode(v->renderer, SDL_BLENDMODE_BLEND);    
}

/*
**Loop for setting the arena rect
*/

void      load_arena(t_visu *v, t_cw *cw, t_parse *p)
{
    int i;
    t_list  *xplr;

    i = 0;
    xplr = p->lst_champs;
    while (xplr->next)
        xplr = xplr->next;
    while (i < MEM_SIZE)
    {
        if (i == ((t_champ*)(xplr->cnt))->mem_pos)
            v->chp_color = v->color_chp[v->chp_n - 1];
        xplr = get_chp_id(xplr, v, p, i);
        if (i % 138 == 0)
            v->count++;
        get_items_cnt(v, cw, i);
        get_arena_texture(v, i, cw);
        i++;
    }
}