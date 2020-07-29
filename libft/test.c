/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 18:36:39 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/22 18:45:03 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int		main(void)
{
	int		*table1;
	int		*table2;
	int		*t3;

	table1 = ft_1D_int_table(3);
	table2 = ft_1D_int_table(5);
	t3 = ft_1D_int_table(10);
	printf("valeur t1[0] = %d | t1[1] = %d | t1[2] = %d\n", table1[0], table1[1], table1[2]);
	printf("valeur t2[0] = %d | t1[2] = %d | t1[4] = %d\n", table2[0], table2[2], table2[4]);
	printf("valeur t3[0] = %d | t3[2] = %d | t3[4] = %d | t3[6] = %d | t3[8] = %d\n", t3[0], t3[2], t3[4], t3[6], t3[8]);
	printf("t1[3] = %d\n", table1[3]);
	return (0);
}