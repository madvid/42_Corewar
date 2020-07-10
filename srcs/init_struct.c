/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:30:11 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/10 11:19:51 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/asm.h"

t_code    *ft_create_elem(void)
{
    t_code *elem;
    
	if (!(elem = malloc(sizeof(t_code))))
		return (NULL);
   // if (!(elem->label = (char*)malloc(sizeof(char) * 10)))
     //   return (NULL);
    if (!(elem->instruction = (char*)malloc(sizeof(char) * 10)))
        return (NULL);
    if (!(elem->hexa_instruction = (char*)malloc(sizeof(char) * 11)))
        return (NULL);
    elem->len = 2;
    elem->position = 0;
    elem->next = NULL;
	return (elem);
}

void    init_head(t_head *h, char *av)
{   
    int     size;

    if ((h->fd = open(av, O_RDONLY)) < 0)
        leave(h, ": Can not open file.s\n");
    if ((h->i = read(h->fd, h->buff, MEM_SIZE + 2)) < 0)
        leave(h, ": Can not read file.s\n");
    h->buff[h->i] = 0;
    h->i = 0;
    size = PROG_NAME_LENGTH + COMMENT_LENGTH;
    if (!(h->header = (char *)malloc(sizeof(char) * size + 13)))
        leave(head, ": Fail to malloc h->header\n");
    if (!(h->hexa_head = (char *)malloc(sizeof(char) * ((size * 2) + 33))))
        leave(head, ": Fail to malloc h->header\n");
}
