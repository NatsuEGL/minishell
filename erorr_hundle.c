/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erorr_hundle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 08:06:42 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/17 13:45:45 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	specifie_type(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		tmp->sep_type = 0;
		if (tmp->command[0] == '|')
		{
			tmp->sep_type = 4;
			tmp->type = 'S';
		}
		else
			specifie_type_norm(&tmp);
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
	if (case_error(&tmp) == -1)
		return (-1);
	return (0);
}

int	case_error(t_list **tmp)
{
	while (*tmp)
	{
		if ((*tmp)->type == 'S')
		{
			if ((*tmp)->command[0] == '|' && ft_strlen((*tmp)->command) > 1)
				return (-1);
			if (ft_strlen((*tmp)->command) > 2)
				return (-1);
			if ((*tmp)->next && !ft_strcmp((*tmp)->command, \
			(*tmp)->next->command))
				return (-1);
			if (!(*tmp)->next)
				return (-1);
			if ((*tmp)->next && (*tmp)->command[0] == '|' && \
			((*tmp)->next->command[0] == '>' || \
			(*tmp)->next->command[0] == '<')) 
				return (0);
			else if ((*tmp)->next && (*tmp)->next->type == 'S')
				return (-1);
		}
		(*tmp) = (*tmp)->next;
	}
	return (0);
}

void	specifie_type_norm(t_list **tmp)
{
	if (!ft_strcmp((*tmp)->command, "<<"))
	{
		(*tmp)->type = 'S';
		(*tmp)->sep_type = 5;
	}
	else if (!ft_strcmp((*tmp)->command, ">>"))
	{
		(*tmp)->sep_type = 3;
		(*tmp)->type = 'S';
	}
	else if ((*tmp)->command[0] == '>')
	{
		(*tmp)->sep_type = 1;
		(*tmp)->type = 'S';
	}
	else if ((*tmp)->command[0] == '<')
	{
		(*tmp)->sep_type = 2;
		(*tmp)->type = 'S';
	}
	else 
		(*tmp)->type = 'W';
}
