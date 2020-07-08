/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 14:33:35 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/08 14:48:43 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long long ft_atoull(const char *str)
{
	unsigned long long	ret;
	int					i;

	i = 0;
	ret = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		ret = ret * 10 + (unsigned long long)(str[i] - '0');
	return (ret);
}