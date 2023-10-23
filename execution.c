/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:53:42 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/23 08:26:26 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builting(t_exec **list, t_env **envp, int data)
{
	t_exec	*tmp;

	tmp = (*list);
	while (tmp)
	{
		b_norm(tmp, envp, data);
		tmp = tmp->next;
	}
}

char	*concatenate_path_len(char *directory, size_t dir_length, char *command)
{
	int		full_len;
	char	*path;

	full_len = dir_length + ft_strlen(command) + 2;
	path = malloc(full_len);
	if (path == NULL)
	{
		perror("malloc");
		exit(1);
	}
	ft_strncpy(path, directory, dir_length);
	path[dir_length] = '/';
	ft_strcpy(path + dir_length + 1, command);
	return (path);
}

char	**check_path_for_command(char *path_var, char *command)
{
	char	*path;
	char	*end;
	int		dir_length;
	char	*full_path;

	path = path_var;
	while (*path != '\0')
	{
		end = path;
		while (*end != '\0' && *end != ':')
			end++;
		dir_length = end - path;
		full_path = concatenate_path_len(path, dir_length, command);
		if (access(full_path, X_OK) == 0)
		{
			if (executable_ret(path, dir_length, command))
				return (executable_ret(path, dir_length, command));
		}
		free(full_path);
		if (*end == ':')
			path = end + 1;
		else
			break ;
	}
	return (NULL);
}

void	execute_cmd(t_exec *exec_val, t_env **envp)
{
	if (list_size(exec_val) < 2)
	{
		if (!builting_check(exec_val->command[0]))
		{
			builting(&exec_val, envp, exec_val->outfile);
			return ;
		}
		else
		{
			simple_command(exec_val, envp);
		}
	}
	else
	{
		multiple_command(exec_val, envp);
	}
}

void	execution_part(t_list **list, t_env **envp)
{
	t_list	*head;
	t_var2	vars;
	t_exec	*n;
	t_exec	*exec_val;	

	head = *list;
	if (!head)
		return ;
	exec_val = malloc(sizeof(t_exec));
	initialination2(&vars);
	initialination(&n, exec_val);
	while (head)
	{
		initialination3(&head, &n, &exec_val);
		if (head)
			(head) = head->next;
		vars.s++;
	}
	n->next = NULL;
	if (n->flag == 1)
	{
		execute_cmd(exec_val, envp);
		free_list_exe(&exec_val);
	}
	else
		return ;
}
