/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:47:52 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/22 10:59:37 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_parsing(t_env *list, t_env **envp)
{
	if (!ft_isalpha(list->c[0]))
	{
		ft_putstr_fd("not a valid identifier\n", 2);
		(*envp)->es = 1;
		return (-1);
	}
	return (1);
}

void	free_env(t_env **list)
{
	if (!(*list))
		return ;
	free((*list)->c);
	free((*list)->v);
	free(*list);
	*list = NULL;
}

void	free_var(t_var3 **list)
{
	if (!(*list))
		return ;
	free((*list)->c);
	free((*list)->v);
	free(*list);
	*list = NULL;
}

void	export_fail_free(t_env *new_env, t_var3 **vars)
{
	free((*vars)->c);
	free(new_env->c);
	free(new_env);
}
