/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:24:26 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/20 16:41:49 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_norm(t_env **prev, t_env **current, t_env **envp)
{
	if ((*prev))
		(*prev)->next = (*current)->next;
	else
		*envp = (*current)->next;
	free((*current)->c);
	free((*current)->v);
	free((*current));
}

void	delete_from_env(t_env **envp, char **p)
{
	t_env	*existing;
	t_env	*prev;
	t_env	*current;
	char	*c;

	p++;
	while (*p)
	{
		c = command_ret(*p);
		existing = find_node(*envp, c);
		if (existing)
		{
			prev = NULL;
			current = *envp;
			while (current && ft_strcmp(current->c, c) != 0)
			{
				prev = current;
				current = current->next;
			}
			if (current)
				unset_norm(&prev, &current, envp);
		}
		free(c);
		p++;
	}
}
