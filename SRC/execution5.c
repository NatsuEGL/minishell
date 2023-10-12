/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:06:12 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/11 22:06:06 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void multiple_command(t_exec *exec_val , t_env **envp)
{
	int n = list_size(exec_val); // how many pipes that i have if it's n - 1
	pid_t pid[3];
	int	**fd;
	int i;
	int j;
	int status;

	i = 1;
	j = 0;
	fd = make_fd(n);
	while(fd[j])
	{
		if (pipe(fd[j]) == -1)
		{
			perror(":pipe fd:");
			exit(0);
		}
		j++;
	}
	pid[0] = first_child(exec_val, envp, fd);
	exec_val = exec_val->next;
	while(i < n - 1)
	{
		pid[1] = middle_child(exec_val, envp, fd, i);
		exec_val = exec_val->next;
		i++;
	}
	pid[2] = last_child(exec_val, envp, fd, (i - 1));
	i = 0;
	while(fd[i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	waitpid(pid[2], &status, 0);
	es = exit_status(status);
	free_double(fd);
	return ;
}

void free_list_exe(t_exec **list)
{
	if (!(*list))
		return ;
	if ((*list)->next)
		free_list_exe(&(*list)->next);
	free((*list)->command);
	free(*list);
	*list = NULL;
}

char *command_slash(char *command)
{
	if (access(command, F_OK | X_OK) == 0)
		return (ft_strdup(command));
	// es = 127;
	return (NULL);
}
