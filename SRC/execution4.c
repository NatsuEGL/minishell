/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:02:54 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/11 20:09:40 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int **make_fd(int n)
{
	int i;
	int **fd;
	
	i = 0;
	fd = malloc(sizeof(int *) * (n));
	while(i < n - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	fd[i] = NULL;
	return (fd);
}

pid_t first_child(t_exec *exec_val, t_env **envp, int **fd)
{
	pid_t pid;
	char *path;
	size_t i;

	pid = fork();
	i = 0;
	if (pid == -1)
	{
		perror(":pid 1st child:");
		exit(1);
	}
	else if (pid == 0)
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
		else
			dup2(fd[0][1], STDOUT_FILENO);
		while(fd[i])
		{
			close(fd[i][0]);
			close(fd[i][1]);
			i++;
		}
		if (!Builting_check(exec_val->command[0]))
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
	return(pid);
}

pid_t middle_child(t_exec *exec_val, t_env **envp, int **fd, size_t i)
{
	pid_t pid;
	char *path;
	size_t j;

	pid = fork();
	j = 0;
	if (pid == -1)
	{
		perror(":pid midlle child:");
		exit(1);
	}
	else if (pid == 0)
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
		while(fd[j])
		{
			close(fd[j][0]);
			close(fd[j][1]);
			j++;
		}
		if (!Builting_check(exec_val->command[0]))
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
	return(pid);
}

pid_t last_child(t_exec *exec_val , t_env **envp, int **fd, int n)
{
	pid_t pid;
	char *path;
	size_t j;

	pid = fork();
	j = 0;
	if (pid == -1)
	{
		perror(":pid last child:");
		exit(1);
	}
	else if (pid == 0)
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
		while(fd[j])
		{
			close(fd[j][0]);
			close(fd[j][1]);
			j++;
		}
		if (!Builting_check(exec_val->command[0]))
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
	return(pid);	
}

void free_double(int **fd)
{
	size_t i;

	i = 0;
	while(fd[i])
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
