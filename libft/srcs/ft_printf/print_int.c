/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 08:21:40 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/04 10:40:53 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

void	print_int(t_data *t)
{
	t->nb_print += write(t->fd, t->bf, (int)ft_strlen(t->bf));
	free(t->bf);
	t->i++;
}