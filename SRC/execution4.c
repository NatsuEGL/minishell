/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:02:54 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/15 22:11:23 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**make_fd(int n)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc(sizeof(int *) * (n));
	while (i < (n - 1))
	{
		fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	fd[i] = NULL;
	return (fd);
}

pid_t	first_child(t_exec *exec_val, t_env **envp, int **fd)
{
	pid_t	pid;
	size_t	i;

	i = 0;
	pid = fork();
	if (pid == -1)
	{
		perror(":pid 1st child:");
		exit(1);
	}
	else if (pid == 0)
	{
		first(exec_val, fd);
		while (fd[i])
		{
			close(fd[i][0]);
			close(fd[i][1]);
			i++;
		}
		exec_func(exec_val, envp);
	}
	return (pid);
}

pid_t	middle_child(t_exec *exec_val, t_env **envp, int **fd, size_t i)
{
	pid_t	pid;
	size_t	j;

	pid = fork();
	j = 0;
	if (pid == -1)
	{
		perror(":pid midlle child:");
		exit(1);
	}
	else if (pid == 0)
	{
		second(exec_val, fd, i);
		while (fd[j])
		{
			close(fd[j][0]);
			close(fd[j][1]);
			j++;
		}
		exec_func(exec_val, envp);
	}
	return (pid);
}

pid_t	last_child(t_exec *exec_val, t_env **envp, int **fd, int n)
{
	pid_t	pid;
	size_t	j;

	pid = fork();
	j = 0;
	if (pid == -1)
	{
		perror(":pid last child:");
		exit(1);
	}
	else if (pid == 0)
	{
		last(exec_val, fd, n);
		while (fd[j])
		{
			close(fd[j][0]);
			close(fd[j][1]);
			j++;
		}
		exec_func(exec_val, envp);
	}
	return (pid);
}

void	free_double(int **fd)
{
	size_t	i;

	i = 0;
	while (fd[i])
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
