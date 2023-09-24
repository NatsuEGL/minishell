/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 08:16:34 by akaabi            #+#    #+#             */
/*   Updated: 2023/09/17 10:53:28 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*fill_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_env;
	int		i;
	int		j;

	head = NULL;
	current = NULL;
	i = 0;
	while (envp[i])
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			return (0);
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		new_env->c = malloc(j + 1);
		new_env->c = ft_strncpy(new_env->c, envp[i], j);
		new_env->c[j] = '\0';
		if (envp[i][j] == '=')
			new_env->v = ft_strdup(envp[i] + j + 1);
		else
			new_env->v = NULL;
		new_env->next = NULL;
		if (!head)
		{
			head = new_env;
			current = new_env;
		}
		else
		{
			current->next = new_env;
			current = new_env;
		}
		i++;
	}
	return (head);
}

int	fun(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (str[i - 1] == '+')
				return (1);
		}
		i++;
	}
	return (0);
}

int	only_alnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
		{
			if (str[i + 1] != '=')
				return (0);
		}
		i++;
	}
	return (1);
}
