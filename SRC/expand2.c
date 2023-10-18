/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 08:42:09 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/12 20:51:51 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	separ_expland(t_list *tmp, t_env **env)
{
	int		i;
	int		j;
	char	*p;
	char	*x;

	i = 0;
	j = 0;
	p = malloc(1);
	p[0] = '\0';
	while (tmp->command[i])
	{
		j = i;
		while (tmp->command[i] && \
			(tmp->command[i] != '\"' && tmp->command[i] != '\''))
			i++;
		x = ft_substr(tmp->command, j, i - j);
		x = normal_expand_helper1(x, env);
		p = ft_strjoin(p, x);
		j = i + 1;
		if (tmp->command[i] == '\"')
		{
			i = find_index(tmp->command, i);
			x = ft_substr(tmp->command, j, i - j);
			x = normal_expand_helper2(x, env);
			i++;
			p = ft_strjoin(p, x);
		}
		else if (tmp->command[i] == '\'')
		{
			i = find_index(tmp->command, i);
			x = ft_substr(tmp->command, j, i - j);
			i++;
			p = ft_strjoin(p, x);
		}
	}
	free(tmp->command);
	tmp->command = ft_strjoin(ft_strdup(""), p);
}

int	find_index(char *p, int i)
{
	if (p[i] == '\"')
	{
		i++;
		while (p[i] && p[i] != '\"')
			i++;
	}
	if (p[i] == '\'')
	{
		i++;
		while (p[i] && p[i] != '\'')
			i++;
	}
	return (i);
}

char	*special_expand(char *p, int *in)
{
	char	*x;
	int		i;
	int		j;

	i = 0;
	p = p + *in;
	if (p[i] == '$')
		p = ft_strdup("$");
	else if (p[i] == '0')
	{
		j = i;
		while (p[i] >= '0' && p[i] <= '9')
			i++;
		x = ft_substr(p, j + 1, i - j);
		p = ft_strdup("");
		p = ft_strjoin(ft_strdup("minishell"), x);
	}
	else if (p[i] >= '1' && p[i] <= '9')
	{
		j = i;
		while (p[i] >= '0' && p[i] <= '9')
			i++;
		p = ft_substr(p, j + 1, i - j);
	}
	else 
		p = ft_strdup("");
	(*in) = (*in) + i;
	return (p);
}
