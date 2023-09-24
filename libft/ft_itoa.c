/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:09:26 by aamhal            #+#    #+#             */
/*   Updated: 2022/11/03 10:06:59 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countnbr(int c)
{
	size_t	count;

	count = 0;
	if (c <= 0)
			count++;
	while (c)
	{
		c /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	*p;
	long	nb;

	i = ft_countnbr(n);
	nb = n;
	p = ft_calloc(sizeof(char), (i + 1));
	if (!p)
		return (0);
	if (nb < 0)
	{
		p[0] = '-';
		nb *= -1;
	}
	if (!nb)
		p[0] = '0';
	while (nb > 0)
	{
		p[i - 1] = nb % 10 + 48;
		nb = nb / 10;
		i--;
	}
	return (p);
}
