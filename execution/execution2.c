/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:56:53 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/15 20:30:22 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	redirection_out(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	redirection_append(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	here_doc(char *Delim)
{
	int		fd[2];
	int		status;
	char	*cmd;
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			cmd = readline("Heredoc> ");
			if (!ft_strcmp(cmd, Delim))
			{
				free(cmd);
				exit(0);
			}
			ft_putstr_fd(cmd, fd[1]);
			write(fd[1], "\n", 1);
			free(cmd);
		}
	}
	waitpid(pid, &status, 0);
	close (fd[1]);
	return (fd[0]);
}

int	list_size(t_exec *exec_val)
{
	t_exec	*head;
	int		size;

	size = 0;
	if (!exec_val)
		return (0);
	head = exec_val;
	while (head)
	{
		size++;
		head = head ->next;
	}
	return (size);
}
