/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:40:11 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/03 18:44:19 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"

char	*errors[NB_ERROR_MSG] =
{
	"Usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ..."
	"Dump error: [-dump nb] nb need to exist, be non null and positive INT."
	"value error: [-n number], n must be either 1, 2, 3 or 4."
	"Champion file error: file must be a bytecode with '.cor' extension."
	"Error: memory allocation issue during parsing process."
	"Error: You must precise 1 champion at least."
	"Error: a maximum of 4 champions is allowed."
	"Error: one of champion's file is not bytecode."
	"Error: Incorrect bytecode in champion's code."
	"Error: Invalid fd, file or path may not exist."
	"Error: COREWAR_EXEC_MAGIC number into file."
}