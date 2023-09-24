/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:38:13 by aamhal            #+#    #+#             */
/*   Updated: 2023/08/24 10:30:31 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*p;
// 	size_t	lent1;
// 	size_t	lent2;
// 	size_t	i;

// 	i = 0;
// 	if (!s1 || !s2)
// 		return (0);
// 	lent1 = ft_strlen(s1);
// 	lent2 = ft_strlen(s2);
// 	p = (char *)malloc((lent1 + lent2 + 1) * sizeof(char));
// 	if (!p)
// 		return (0);
// 	ft_memcpy(p, s1, lent1);
// 	ft_memcpy(p + lent1, s2, lent2);
// 	p[lent1 + lent2] = '\0';
// 	free ((char *)s1);
// 	return (p);
// }
