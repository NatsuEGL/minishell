/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:47:52 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/23 14:17:55 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_parsing(t_env *list, t_env **envp, t_var3 **vars)
{
	if (!ft_isalpha(list->c[0]))
	{
		ft_putstr_fd("not a valid identifier\n", 2);
		(*envp)->es = 1;
		if ((*vars)->v)
			free((*vars)->v);
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

char    *check_ex(char *p)
{
    int i;
    char c;
    int count;
    
    i = 1;
    count = 0;
    if (p[0] == '\'' || p[0] == '\"')
        c = p[0];
    while (p[i])
    {
        if (c == '\"' && p[i] == '\'')
            return (0);
        else if (c == '\'' && p[i] == '\"')
            return (0);
		else if (p[i] == c)
			break ;   
            count++;
        i++;
    }
    while(count--)
        p = q_remouve(p);
    return (p);
}
