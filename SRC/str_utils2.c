// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   str_utils2.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/08/19 08:11:35 by akaabi            #+#    #+#             */
// /*   Updated: 2023/08/20 06:40:57 by akaabi           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// void	*ft_memcpy(void *dst, const void *src, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!src && !dst)
// 		return (0);
// 	if (src == dst)
// 		return (dst);
// 	while (i < n)
// 	{
// 		((char *)dst)[i] = ((char *)src)[i];
// 		i++;
// 	}
// 	return (dst);
// }

// char	*ft_strjoin(char *s1, char*s2)
// {
// 	int		str1;
// 	int		str2;
// 	char	*p;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	str1 = ft_strlen (s1);
// 	str2 = ft_strlen (s2);
// 	p = malloc(sizeof(char) * (str1 + str2) + 1);
// 	if (!p)
// 		return (0);
// 	ft_memcpy(p, s1, str1);
// 	ft_memcpy((p + str1), s2, str2);
// 	p[str1 + str2] = '\0';
//     free(s1);
//     // free(s2);
// 	return (p);
// }
