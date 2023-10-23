/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 08:37:36 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/21 11:47:50 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_list **list, t_env **env)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		while_expand(&tmp, env);
		tmp = tmp->next;
	}
}

void	check_expand(t_list *tmp, t_env **env)
{
	int	i;

	i = 0;
	while (tmp->command[i])
	{
		if (tmp->command[i] == '\"' || tmp->command[i] == '\'')
		{
			separ_expand(tmp, env);
			return ;
		}
		i++;
	}
	normal_expand(tmp, env);
}

int	ft_check_ex(char *p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (p[i] == '$' && !ft_isalnum(p[i + 1]) && p[i + 1] != '_')
			return (0);
		i++;
	}
	return (-1);
}

char	*check_env_q(char *p, t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (!ft_strcmp(p, tmp->c))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		if (ft_check_ex(p) == -1)
			return (free(p), NULL);
		p = ft_strjoin(ft_strdup("$"), p);
		return (p);
	}
	free(p);
	return (ft_strdup(tmp->v));
}

char	*check_env(char *p, t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (!ft_strcmp(p, tmp->c))
			break ;
		tmp = tmp->next;
	}
	free(p);
	if (!tmp)
		return (NULL);
	return (ft_strdup(tmp->v));
}
