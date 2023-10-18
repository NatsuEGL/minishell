/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:06:12 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/17 22:20:56 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	multiple_command(t_exec *exec_val, t_env **envp)
{
	pid_t	pid[3];
	int		n;
	int		**fd;
	int		i;
	int		status;

	n = list_size(exec_val);
	fd = make_fd(n);
	multi_cmd_fd(fd);
	i = 1;
	pid[0] = first_child(exec_val, envp, fd);
	exec_val = exec_val->next;
	while (i < n - 1)
	{
		pid[1] = middle_child(exec_val, envp, fd, i);
		exec_val = exec_val->next;
		i++;
	}
	pid[2] = last_child(exec_val, envp, fd, (i - 1));
	multi_cmd_fd_close(fd);
	i = 0;
	while (i < 3)
		waitpid(pid[i++], &status, 0);
	free_double(fd);
	return ;
}

void	free_list_exe(t_exec **list)
{
	if (!(*list))
		return ;
	if ((*list)->next)
		free_list_exe(&(*list)->next);
	free_doublep((*list)->command);
	free(*list);
	*list = NULL;
}

char	*command_slash(char *command)
{
	if (access(command, F_OK | X_OK) == 0)
		return (ft_strdup(command));
	printf_error(command);
	return (NULL);
}

void	free_doublep(char **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		free(command[i]);
		i++;
	}
	free(command);
}
