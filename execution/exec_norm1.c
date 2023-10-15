/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_norm1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 21:03:03 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/15 21:12:32 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exec_func(t_exec *exec_val, t_env **envp)
{
    char *path;

    if (!builting_check(exec_val->command[0]))
	{
		builting(&exec_val, envp, exec_val->outfile);
		exit (0);
	}
    path = searching_path(exec_val->command[0], envp);
	free(exec_val->command[0]);
	exec_val->command[0] = ft_strdup(path);
	free(path);
	execve(exec_val->command[0], exec_val->command, (*envp)->envir);
}
