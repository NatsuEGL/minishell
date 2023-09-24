/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:14:04 by aamhal            #+#    #+#             */
/*   Updated: 2023/08/24 09:02:42 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	size;

	i = -1;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || *s == '\0')
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		size = ft_strlen(s) - start + 1;
	else
		size = len + 1;
	p = ft_calloc(size, sizeof(char));
	if (!p)
		return (NULL);
	if (start >= ft_strlen(s))
		return (p);
	while (++i < len && s[start + i])
		p[i] = s[start + i];
	return (p);
}
