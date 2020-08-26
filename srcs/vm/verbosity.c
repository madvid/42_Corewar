/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbosity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:46:05 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/26 17:42:29 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		verbotab(t_cw *cw, t_process *p, t_arg arg)
{
	// verbotab[0] = &vprint_essentials;
	// verbotab[1] = &vprint_lives;
	// verbotab[2] = &vprint_cycle;
	// verbotab[3] = &vprint_op;
	// verbotab[4] = &vprint_deaths;
	// verbotab[5] = &vprint_pcmv;
	(cw->options->v_lvl & 0b00000100) ? vprint_op();
	(cw->options->v_lvl & 0b00000001) && vprint_lives();
	(cw->options->v_lvl & 0b00000010) ? vprint_cycle();
	(cw->options->v_lvl & 0b00010000) ? vprint_pcmv();
}

int		vprint_essentials(t_cw *cw, void *ptr, t_arg a, int flag)
{
	if (cw || ptr || !a.type[0])
		return (flag);
	return (flag);
}

char		*ito_arg(char *s, int n)
{
	unsigned int	u;
	char			c[2];

	if (n < 0)
	{
		s = ft_strcat(s, "-");
		u = -n;
	}
	else
		u = n;
	c[0] = u % 10 + '0';
	c[1] = 0;
	if (u > 9)
		ito_arg(s, u / 10);
	s = ft_strcat(s, c);
	return (s);
}

char		*args_to_str(t_arg a)
{
	char	*str;
	int		i;

	if (!(str = ft_strnew(128)))
		return (NULL);
	i = -1;
	while (++i < 3 && a.type[i] != 0)
	{
		if (a.type[i] == REG_CODE)
			str = ft_strcat(str, "r");
		str = ito_arg(str, a.arg[i]);
		if ((i + 1) < 3 && a.type[i + 1] != 0)
			str = ft_strcat(str, " ");
	}
	return (str);
}