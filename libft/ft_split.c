/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:09:36 by aamhal            #+#    #+#             */
/*   Updated: 2022/11/03 21:27:25 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(const char str, const char c)
{
	if (str == c)
		return (1);
	return (0);
}

static char	*trim(char const *s1, char const set)
{
	char	*p;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	if (!s1)
		return (0);
	j = ft_strlen(s1) - 1;
	while (*s1 && (ft_check(set, (char)s1[i])))
		i++;
	while (j && *s1 && (ft_check(set, (char)s1[j])))
		j--;
	len = j - i + 1;
	if (j > i)
	{
		p = ft_substr(s1, i, len);
	}
	else
		p = ft_substr(s1, i, 1);
	return (p);
}

static int	word_count(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	if (!s)
		return (0);
	count = 1;
	while (s[i])
	{
		if (s[i] == c)
		{
			count++;
			while (s[i] && s[i] == c)
				i++;
			i--;
		}
		i++;
	}
	return (count);
}

static char	**ft_error(char **s, size_t e)
{
	size_t	i;

	i = 0;
	while (i < e)
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
	s = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	char	*str;
	int		i;
	int		start;
	int		end;	

	str = trim(s, c);
	p = (char **)ft_calloc((word_count(str, c) + 1), sizeof(char *));
	if (!p || !s)
		return (free(p), NULL);
	i = -1;
	start = 0;
	end = 0;
	while (str[++i] && i < word_count(str, c))
	{
		while (str[end] && str[end] != c)
			end++;
		p[i] = ft_substr(str, start, end - start);
		if (!p)
			return (ft_error(p, i));
		while (str[end] == c)
			end++;
		start = end;
	}
	return (free(str), p);
}
