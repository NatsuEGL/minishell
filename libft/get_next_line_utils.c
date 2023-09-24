/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 09:45:15 by aamhal            #+#    #+#             */
/*   Updated: 2023/09/17 09:43:33 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char	*s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*p;
	size_t	lent1;
	size_t	lent2;
	size_t	i;

	i = 0;
	lent1 = ft_strlen(s1);
	lent2 = ft_strlen(s2);
	p = (char *)malloc((lent1 + lent2 + 1) * sizeof(char));
	if (!p)
		return (0);
	ft_memcpy(p, s1, lent1);
	ft_memcpy(p + lent1, s2, lent2);
	p[lent1 + lent2] = '\0';
	free((char *)s1);
	free((char *)s2);
	return (p);
}

int	ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*src;

	i = 0;
	while (s1[i] != '\0')
		i++;
	src = malloc(i * sizeof(char) + 1);
	if (!src)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		src[i] = s1[i];
		i++;
	}
	src[i] = '\0';
	return (src);
}
