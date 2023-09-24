/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:29:58 by aamhal            #+#    #+#             */
/*   Updated: 2022/10/25 11:47:46 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*p;
	size_t	lent;

	i = 0;
	lent = ft_strlen(s);
	if (!s || !f)
		return (0);
	p = (char *)malloc(sizeof(char) * lent + 1);
	if (!p)
		return (0);
	while (s[i])
	{
		p[i] = (*f)(i, (char)s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
