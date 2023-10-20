/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:46:55 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/20 16:31:23 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	existing_norm(char **p, t_var3 **vars, t_env **existing)
{
	if (!ft_strcmp((*vars)->c, "_"))
		(*vars)->i = 0;
	else if (fun(*p) == 1)
	{
		if ((*existing)->v && (*vars)->v)
		{
			(*vars)->v2 = ft_strjoin((*existing)->v, (*vars)->v);
			(*existing)->v = ft_strdup((*vars)->v2);
		}
	}
	else
	{
		if (!(*vars)->v)
			return ;
		free((*existing)->v);
		(*existing)->v = ft_strdup((*vars)->v);
	}
}

void	not_exesting(char **p, t_env **new_env, t_var3 **vars)
{
	(*vars)->c = command_ret(*p);
	(*new_env)->c = ft_strdup((*vars)->c);
	if (ft_isdigit((*new_env)->c[0]) == 1)
	{
		printf("not a valid identifier\n");
		exit(1);
	}
	(*vars)->v = value_ret(*p);
	(*new_env)->v = (*vars)->v;
}

void	not_exesting2(t_env **new_env, t_var3 **vars)
{
	(*new_env)->c = ft_strdup((*vars)->c);
	if (ft_isdigit((*new_env)->c[0]) == 1)
	{
		printf("not a valid identifier\n");
		exit(1);
	}
	if (!(*vars)->v)
		(*new_env)->v = ft_strdup("");
	else
		(*new_env)->v = ft_strdup((*vars)->v);
}

void	not_exesting_norm(t_env *new_env, t_var3 **vars, char **p, t_env **envp)
{
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return ;
	(*vars)->equal = ft_strchrr(*p, '=');
	if (!(*vars)->equal)
		not_exesting(p, &new_env, vars);
	else
		not_exesting2(&new_env, vars);
	new_env->next = NULL;
	free((*vars)->c);
	free((*vars)->v);
	ft_lstadd_back1(envp, new_env);
}

void	export_initialisation(char **p, t_var3 **vars, \
t_env **envp, t_env **existing)
{
	(*vars)->c = command_ret(*p);
	(*vars)->v = value_ret(*p);
	(*existing) = find_node(*envp, (*vars)->c);
}
