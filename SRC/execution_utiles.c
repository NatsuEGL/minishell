/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:38:14 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/10 15:17:44 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_if_separ(t_list **list, char *separ)
{
	t_list *tmp = (*list);
	while (tmp)
	{
		if (!ft_strcmp(tmp->command, separ) && tmp->type == 'S')
			return (0);
		tmp = tmp->next;
	}
	return (-1);
}

// void exec_command(t_list **list, t_env **envp)
// {
// 	char *path_var;
// 	char **executable_info;

// 	path_var = check_env(ft_strdup("PATH"), envp);
// 	executable_info = check_path_for_command(path_var, (*list)->command);
//     if (executable_info != NULL)
// 	{
//         printf("Executing command: %s\n", executable_info[0]);
//         execute_command(executable_info);
//         free(executable_info);
//     }
// 	else
//         printf("Command '%s' not found in PATH.\n", (*list)->command);
// }

// char *delimiter(t_list **list)
// {
// 	t_list *tmp = *list;
	
// 	while(tmp)
// 	{
// 		if (tmp->type == 'D')
// 			return (tmp->command);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }
