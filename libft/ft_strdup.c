/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:36:12 by aamhal            #+#    #+#             */
/*   Updated: 2022/11/03 10:06:47 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	s_lent;
	char	*p;

	s_lent = ft_strlen(s1);
	p = (char *)malloc((s_lent + 1) * sizeof(char));
	if (!p)
		return (0);
	ft_strlcpy(p, s1, s_lent + 1);
	return (p);
}
