/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 22:26:25 by aamhal            #+#    #+#             */
/*   Updated: 2022/11/03 21:09:31 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	d;

	i = 0;
	d = (unsigned char)c;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == d)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
