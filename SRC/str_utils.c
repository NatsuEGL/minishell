/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 08:15:30 by akaabi            #+#    #+#             */
/*   Updated: 2023/08/22 08:15:40 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_strncpy(char *dst, char *src, int n)
{
    int i = 0;
    
    while (i < n && src[i])
    {
        dst[i] = src[i];
        i++;
    }
    return (dst);
}

int	ft_strcmp1(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
