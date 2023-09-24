/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:33:16 by aamhal            #+#    #+#             */
/*   Updated: 2022/11/15 15:05:43 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthexa(unsigned int nbr, int *count, char c)
{
	if (nbr <= 9)
		ft_putchar(nbr + '0', count);
	else if (nbr > 9 && nbr < 16)
	{
		if (c == 'u')
			ft_putchar("ABCDEF"[nbr % 10], count);
		if (c == 'l')
			ft_putchar("abcdef"[nbr % 10], count);
	}
	else
	{
		ft_puthexa(nbr / 16, count, c);
		ft_puthexa(nbr % 16, count, c);
	}
}
