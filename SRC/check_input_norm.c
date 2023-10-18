/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_norm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:58:02 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/15 21:14:05 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quot_norm(char *cmd, int i, int j, char *c, char **p)
{
	*c = '\0';
	*p = malloc(1);
	*p[0] = '\0';
	j = i;
	if (cmd[i] && (cmd[i] == '\'' || cmd[i] == '\"'))
	{
		*c = cmd[i];
		i = find_index(cmd, i);
		*p = ft_strjoin(*p, ft_substr(cmd, j, i - j + 1));
		i++;
	}
	return (i);
}