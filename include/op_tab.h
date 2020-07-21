/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tab.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:52:24 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/21 16:53:47 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct					s_op
{
	char				*name;
	size_t				n_arg;
	size_t				type[MAX_ARGS_NUMBER];
	size_t				code;
	size_t				cycle;
	char				*desc;
	size_t				encod;
	size_t				direct_size;
}								t_op;
// direct_size == 0 => 4 - (0 * 2) octets pour l’argument direct
// direct_size == 1 => 4 - (1 * 2) octets pour l’argument direct