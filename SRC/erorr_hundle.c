/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erorr_hundle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 08:06:42 by aamhal            #+#    #+#             */
/*   Updated: 2023/09/18 09:16:39 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	specifie_type(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->command[0] == '|' || tmp->command[0] == '>' || \
		tmp->command[0] == '<')
			tmp->type = 'S';
		else
			tmp->type = 'W';
		tmp = tmp->next;
	}
}

int	cont_char(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = find_index(str, i);
			if (!str[i])
				return (-1);
		}
		i++;
	}
	return (0);
}

int	syntax_error(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == 'W')
		{
			if (cont_char(tmp->command) == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	tmp = *list;
	if (tmp && (tmp->type == 'S' && tmp->command[0] == '|'))
		return (-1);
	while (tmp)
	{
		if (tmp->type == 'S')
		{
			if (tmp->command[0] == '|' && ft_strlen(tmp->command) > 1)
				return (-1);
			if (ft_strlen(tmp->command) > 2)
				return (-1);
			if (tmp->next && !ft_strcmp(tmp->command, tmp->next->command))
				return (-1);
			if (!tmp->next)
				return (-1);
			if (tmp->next && tmp->command[0] == '|' && \
			(tmp->next->command[0] == '>' || \
			tmp->next->command[0] == '<')) 
				return (0);
			else if (tmp->next && tmp->next->type == 'S')
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}
