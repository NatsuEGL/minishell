/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:43:51 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/20 16:54:44 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_norm(t_env **new_env, char **envp, int *i, int *j)
{
	(*new_env)->c = malloc(*j + 1);
	(*new_env)->c = ft_strncpy((*new_env)->c, envp[*i], *j);
	(*new_env)->c[*j] = '\0';
	if (envp[*i][*j] == '=')
		(*new_env)->v = ft_strdup(envp[*i] + *j + 1);
	else
		(*new_env)->v = NULL;
	(*new_env)->next = NULL;
}

void	env_norm2(t_env **head, t_env **current, t_env **new_env)
{
	if (!(*head))
	{
		(*head) = (*new_env);
		(*current) = (*new_env);
	}
	else
	{
		(*current)->next = (*new_env);
		(*current) = (*new_env);
	}
}
