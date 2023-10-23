/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:53:34 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/21 11:53:30 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_back_free(char *p)
{
	free(p);
	return (ft_strdup("/"));
}

void	r_q(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		str[i] = q_remouve(str[i]);
		i++;
	}
}

void	minishell_case(t_env **env, t_list **list)
{
	t_env	*envp;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = (*list);
	envp = (*env);
	while (tmp)
	{
		if (!ft_strcmp(tmp->command, "./minishell"))
		{
			while (envp)
			{
				printf("hi\n");
				if (!ft_strcmp(ft_strdup("SHLVL"), envp->c))
				{
					i = ft_atoi(envp->v) + 1;
					envp->v = ft_itoa(i);
				}
				envp = envp->next;
			}
		}
		tmp = tmp->next;
	}
}

void	while_expand(t_list **tmp, t_env **env)
{
	int	i;

	i = 0;
	while ((*tmp)->command[i])
	{
		if ((*tmp)->command[i] == '\"' && (*tmp)->command[i + 1] == '$' \
		&& (*tmp)->command[i + 2] == '\"')
			break ;
		if ((*tmp)->command[i] == '$' && (*tmp)->command[i + 1] == '\0')
			break ;
		if ((*tmp)->command[i] == '$' && (*tmp)->command[i + 1] == '?')
		{
			(*tmp)->command = ft_itoa((*env)->es);
			break ;
		}
		if ((*tmp)->command[i] == '$')
		{
			(*env)->flag = 1;
			check_expand((*tmp), env);
			break ;
		}
		i++;
	}
}
