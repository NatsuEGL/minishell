/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:24:26 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/07 20:20:56 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    delete_from_env(t_env **envp, char **p)
{
    t_env   *existing;
    char    *c;

    p++;
    while (*p){
        
    c = command_ret(*p);
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
    p++;
    }
}
