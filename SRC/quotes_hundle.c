/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_hundle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 10:52:51 by aamhal            #+#    #+#             */
/*   Updated: 2023/09/17 10:38:10 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*q_remouve(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*p;

	i = 0;
	j = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			len++;
		i++;
	}
	i = 0;
	p = malloc(len + 1);
	p[len] = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			p[j] = str[i];
			i++;
			j++;
		}
		else
			i++;
	}
	return (p);
}
