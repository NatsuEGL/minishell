/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:24:26 by akaabi            #+#    #+#             */
/*   Updated: 2023/09/17 11:19:38 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    delete_from_env(t_env **envp, char *p)
{
    t_env   *existing;
    char    *c;

    c = command_ret(p);
    existing = find_node(*envp, c);
    if (existing)
    {
        t_env *prev = NULL;
        t_env *current = *envp;

        while (current && ft_strcmp(current->c, c) != 0)
        {
            prev = current;
            current = current->next;
        }
        if (current)
        {
            if (prev)
                prev->next = current->next;
            else
                *envp = current->next;
            free(current->c);
            free(current->v);
            free(current);
        }
        else
            return ;
    }
    free(c);
}
