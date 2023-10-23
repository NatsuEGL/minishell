/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_norm2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 22:05:53 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/23 08:40:22 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	second(t_exec *exec_val, int **fd, size_t i)
{
	if (exec_val->infile != STDIN_FILENO)
	{
		dup2(exec_val->infile, STDIN_FILENO);
		close(exec_val->infile);
	}
	else
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (exec_val->outfile != STDOUT_FILENO)
	{
		dup2(exec_val->outfile, STDOUT_FILENO);
		close(exec_val->outfile);
	}
	else
		dup2(fd[i][1], STDOUT_FILENO);
}

void	last(t_exec *exec_val, int **fd, int n)
{
	if (exec_val->infile != STDIN_FILENO)
	{
		dup2(exec_val->infile, STDIN_FILENO);
		close(exec_val->infile);
	}
	else
		dup2(fd[n][0], STDIN_FILENO);
	if (exec_val->outfile != STDOUT_FILENO)
	{
		dup2(exec_val->outfile, STDOUT_FILENO);
		close(exec_val->outfile);
	}
}

void	multi_cmd_fd(int **fd)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		if (pipe(fd[i]) == -1)
		{
			perror(":pipe fd:");
			exit(1);
		}
		i++;
	}
}

void	multi_cmd_fd_close(int **fd)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

char	**executable_ret(char *path, int dir_length, char *command)
{
	char	**executable;
	char	*full_path;

	full_path = concatenate_path_len(path, dir_length, command);
	executable = malloc(2 * sizeof(char *));
	if (executable == NULL)
	{
		perror("malloc");
		free_doublep(executable);
		free(full_path);
		exit (1);
	}
	executable[0] = full_path;
	executable[1] = NULL;
	return (executable);
}
