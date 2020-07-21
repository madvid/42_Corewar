/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:55:59 by weilin            #+#    #+#             */
/*   Updated: 2018/11/23 14:58:03 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_int_len(int n)
{
	int	len;

	len = 1;
	if (n == 0)
		return (len);
	else if (n < 0)
		len++;
	while (n)
	{
		if (n /= 10)
			len++;
	}
	return (len);
}