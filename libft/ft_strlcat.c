/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:15:22 by aamhal            #+#    #+#             */
/*   Updated: 2022/11/03 21:12:27 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_lent;
	size_t	src_lent;

	src_lent = ft_strlen(src);
	if (dstsize == 0 && !dst)
		return (src_lent);
	dst_lent = ft_strlen(dst);
	i = 0;
	if (!dstsize || dstsize <= dst_lent)
		return (dstsize + src_lent);
	j = dst_lent;
	while (src[i] && (i < dstsize - dst_lent - 1))
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (dst_lent + src_lent);
}
