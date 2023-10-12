/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:01:31 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/11 21:56:44 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *searching_path(char *command, t_env **envp)
{
	if (ft_strchr(command, '/'))
		return (command_slash(command));
	char *path = check_env(ft_strdup("PATH"), envp);
	char **path_splied = check_path_for_command(path, command);
	return(path_splied[0]);
}

int	Builting_check(char *command)
{
	if (!ft_strcmp(command, "env")
		|| !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "echo")
		|| !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "exit"))
		return (0);
	return (1);
}

void	simple_command(t_exec *exec_val, t_env **envp)
{
	pid_t pid ;
	char *path;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (exec_val->infile != STDIN_FILENO)
		{
			dup2(exec_val->infile, STDIN_FILENO);
			close(exec_val->infile);	
		}
		if (exec_val->outfile != STDOUT_FILENO)
		{
			dup2(exec_val->outfile, STDOUT_FILENO);
			close(exec_val->outfile);
		}
		path = searching_path(exec_val->command[0], envp);
		free(exec_val->command[0]);
		exec_val->command[0] = ft_strdup(path);
		free(path);
		execve(exec_val->command[0], exec_val->command, (*envp)->envir);
	}
	waitpid(pid, NULL, 0);
	if (exec_val->infile != STDIN_FILENO)
		close(exec_val->infile);
	if (exec_val->outfile != STDOUT_FILENO)
		close(exec_val->outfile);
	return ;
}
