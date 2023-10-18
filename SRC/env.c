/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 08:16:34 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/18 09:18:43 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_ofenv(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

t_env	*filling_env(t_env *a, char **env)
{
	int	i;
	int	size;

	i = 0;
	size = size_ofenv(env);
	a->envir = malloc(sizeof(char *) * size);
	while (env[i])
	{
		a->envir[i] = ft_strdup(env[i]);
		i++;
	}
	return (a);
}

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
	head = filling_env(head, envp);
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
