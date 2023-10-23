/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:46:55 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/23 14:19:42 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	existing_norm(char **p, t_var3 **vars, t_env **existing)
{
	if (!ft_strcmp((*vars)->c, "_"))
		(*vars)->i = 0;
	else if (fun(*p) == 1)
	{
		free((*vars)->c);
		if ((*existing)->v && (*vars)->v)
			(*existing)->v = ft_strjoin((*existing)->v, ft_strdup((*vars)->v));
		free((*vars)->v);
	}
	else
	{
		if (!(*vars)->v)
		{
			free((*vars)->c);
			free((*vars)->v);
			return ;
		}
		free((*vars)->c);
		free((*existing)->v);
		(*existing)->v = ft_strdup((*vars)->v);
		free((*vars)->v);
	}
}

int	not_exesting(char **p, t_env **new_env, t_var3 **vars, t_env **envp)
{
	(*new_env)->c = ft_strdup((*vars)->c);
	if (export_parsing(*new_env, envp ,vars) == -1)
		return (-1);
	(*vars)->v = value_ret(*p);
	(*new_env)->v = (*vars)->v;
	if (!(*new_env)->v)
		(*new_env)->flag2 = 1;
	return (0);
}

int	not_exesting2(t_env **new_env, t_var3 **vars, t_env **envp)
{
	(*new_env)->c = ft_strdup((*vars)->c);
	if (export_parsing(*new_env, envp, vars) == -1)
		return (-1);
	if (!(*vars)->v)
		(*new_env)->v = ft_strdup("");
	else
		(*new_env)->v = ft_strdup((*vars)->v);
	return (0);
}

int	not_exesting_norm(t_env *new_env, t_var3 **vars, char **p, t_env **envp)
{
	new_env = malloc(sizeof(t_env));
	(*vars)->equal = ft_strchrr(*p, '=');
	if (!(*vars)->equal)
	{
		if (not_exesting(p, &new_env, vars, envp) == -1)
		{
			export_fail_free(new_env, vars);
			return (-1);
		}
		free((*vars)->c);
		if ((*vars)->v)
			free((*vars)->v);
	}
	else
	{
		if (not_exesting2(&new_env, vars, envp) == -1)
		{
			export_fail_free(new_env, vars);
			return (-1);
		}
		free((*vars)->c);
		free((*vars)->v);
	}
	new_env->next = NULL;
	ft_lstadd_back1(envp, new_env);
	return (0);
}

void	export_initialisation(char **p, t_var3 **vars, \
t_env **envp, t_env **existing)
{
	(*vars)->c = command_ret(*p);
	(*vars)->v = value_ret(*p);
	(*envp)->flag2 = 0;
	(*existing) = find_node(*envp, (*vars)->c);
}
