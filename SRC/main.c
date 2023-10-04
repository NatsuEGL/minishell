/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 07:29:08 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/03 18:39:10 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 void    print_nodes2(t_list *s)
{
    t_list    *current;

    current = s;
    while (current != NULL)
    {
        printf("[%s]---------[%c]\n", current ->command, current->type);
        current = current->next;
    }
}

void    print_nodes(t_env *s)
{
    t_env    *current;

    current = s;
    while (current != NULL)
    {
        printf("%s=%s\n", current ->c,current->v);
        current = current->next;
    }
}

// void v()
// {
//     system("leaks minishell");
// }

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
    int i = 0;
    int j = 0;
    t_env *head = NULL;
	t_list *list = NULL; 
	char **envp;
  
    // catch_signals();
    while(env[i])
        i++;
    envp = malloc(sizeof(char *) * (i + 1));
    envp[i] = NULL;
    j = i;
    i = 0;
    while(i < j)
    { 
        envp[i] = env[i];
        i++;
    }
    head = fill_list(envp);
	parsing(&list, &head);
	return (0);
}
