/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_hundle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 10:52:51 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/21 09:44:17 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*q_remouve(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*p;
	char	*x;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\'' && str[i] != '\"')
		i++;
	if (str[i] == '\0')
		return (str);
	x = ft_substr(str, 0, i);
	len = find_index(str, i);
	i++;
	p = malloc(len - i + 1);
	p[len - i] = 0;
	while (i < len)
		r_q_norm(str, &p, &i, &j);
	p = ft_strjoin(x, p);
	j = ft_strlen(str);
	x = ft_substr(str, i + 1, j);
	p = ft_strjoin(p, x);
	free(str);
	return (p);
}

void	r_q_norm(char *str, char **p, int *i, int *j)
{
	(*p)[*j] = str[*i];
	*i = *i + 1;
	*j = *j + 1;
}
