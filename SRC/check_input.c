/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 21:35:10 by aamhal            #+#    #+#             */
/*   Updated: 2023/09/17 10:52:46 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(t_list **list, char *cmd, int i)
{
	t_list	*new;
	char	c;
	char	*p;
	int		j;

	p = malloc(1);
	p[0] = '\0';
	while (cmd[i])
	{
		j = i;
		if (cmd[i] && (cmd[i] == '\'' || cmd[i] == '\"'))
		{
			c = cmd[i];
			i = find_index(cmd ,i);
			p = ft_strjoin(p, ft_substr(cmd, j, i-j + 1));
			i++;
		}
		j = i;
		while ((cmd[i] && cmd[i] != '\'' && cmd[i] != '\"'))
		{
			if (cmd[i] && cmd[i] == ' ')
				break ;
			i++;
		}
		p = ft_strjoin(p, ft_substr(cmd, j, i - j));
		if (cmd[i] && cmd[i] == ' ')
		{
			i++;
			break ;
		}
	}
	new = ft_lstnew(p);
	if (!list)
		exit(1);
	ft_lstadd_back(list, new);
	return (i);
}

int	char_quote(char *cmd, int i)
{
	char	c;
	int		j;

	while (cmd[i])
	{
		j = i;
		if (cmd[i] && (cmd[i] == '\'' || cmd[i] == '\"'))
		{
			c = cmd[i];
			i = find_index(cmd, i);
			i++;
		}
		j = i;
		while ((cmd[i] && cmd[i] != '\'' && cmd[i] != '\"'))
		{
			if (cmd[i] && cmd[i] == ' ')
				break ;
			i++;
		}
		if (cmd[i] && cmd[i] == ' ')
		{
			i++;
			break ;
		}
	}
	return (i);
}

int	is_separ(t_list **list, char *cmd, int i)
{
	t_list	*new;
	char	c;
	int		j;

	c = cmd[i];
	j = i;
	while (cmd[j] && cmd[j] == c)
		j++;
	new = ft_lstnew(ft_substr(cmd, i, (j - i)));
	if (!list)
		exit(2);
	ft_lstadd_back(list, new);
	return (j);
}

int	is_char(t_list **list, char *cmd, int i)
{
	int		j;
	t_list	*new;

	j = i; 
	while (cmd[i])
	{
		if (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t' || \
		cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<'))
			break ;
		if (cmd[i] && (cmd[i] == '\'' || cmd[i] == '\"'))
		{
			i = char_quote(cmd, i);
			break ;
		}
		i++;
	}
	new = ft_lstnew(ft_substr(cmd, j, (i - j)));
	ft_lstadd_back(list, new);
	return (i);
}
