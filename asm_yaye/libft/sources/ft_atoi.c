/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:07:25 by yaye              #+#    #+#             */
/*   Updated: 2019/04/02 20:07:26 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long long	ft_llupower(int x, int power)
{
	if (power < 0)
		return (0);
	if (power > 0)
		return (x * ft_llupower(x, power - 1));
	return (1);
}

int					ft_atoi(const char *str)
{
	int					i;
	int					signe;
	unsigned long long	atoi;

	i = 0;
	signe = 1;
	atoi = 0;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == ' ' ||
		str[i] == '\n' || str[i] == '\r' || str[i] == '\v')
		i = i + 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i = i + 1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((unsigned long long)atoi * 10 + (str[i] - '0') \
			>= ft_llupower(2, 63))
			return ((signe < 0) ? 0 : -1);
		atoi = atoi * 10 + (str[i] - '0');
		i = i + 1;
	}
	return (atoi * signe);
}
