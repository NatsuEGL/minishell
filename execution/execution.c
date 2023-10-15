/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:53:42 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/15 21:01:34 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builting(t_exec **list, t_env **envp, int data)
{
	t_exec	*tmp;
	char	*path;

	tmp = (*list);
	while (tmp)
	{
		if (!ft_strcmp(tmp->command[0], "export"))
		{
			if (!tmp->command[1])
				print_node_export((*envp), data);
			else
				update_or_add_env(envp, tmp->command);
		}
		else if (!ft_strcmp(tmp->command[0], "unset"))
		{
			delete_from_env(envp, tmp->command);
		}
		else if (!ft_strcmp(tmp->command[0], "env"))
		{
			path = check_env(ft_strdup("PATH"), envp);
			if (!path)
			{
				printf("env: No such file or directory\n");
				return ;
			}
			print_nodes(*envp, data);
		}
		else if (!ft_strcmp(tmp->command[0], "echo"))
			echo_command(tmp->command, data);
		else if (!ft_strcmp(tmp->command[0], "cd"))
			cd_command(tmp->command, envp);
		else if (tmp->command[0][0] == 'p' || tmp->command[0][0] == 'P')
			pwd_command(tmp->command[0], envp, data);
		else if (!ft_strcmp(tmp->command[0], "exit"))
			exit_command(tmp->command, data, *list);
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
	char	**executable_info;

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
			executable_info = malloc(2 * sizeof(char *));
			if (executable_info == NULL)
			{
				perror("malloc");
				free_doublep(executable_info);
				free(full_path);
				exit (1);
			}
			executable_info[0] = full_path;
			executable_info[1] = NULL;
			return (executable_info);
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
	if (list_size(exec_val) > 1)
	{
		multiple_command(exec_val, envp);
	}
	else
	{
		if (!builting_check(exec_val->command[0]))
		{
			builting(&exec_val, envp, exec_val->outfile);
			return ;
		}
		else
			simple_command(exec_val, envp);
	}
}

void	execution_part(t_list **list, t_env **envp)
{
	t_list	*head;
	t_list	*current;
	int		i;
	int		len;
	int		s;
	t_exec	*n;
	t_exec	*exec_val;	

	i = 0;
	len = 0;
	s = 0;
	head = *list;
	exec_val = malloc(sizeof(t_exec));
	n = exec_val;
	n->infile = STDIN_FILENO;
	n->outfile = STDOUT_FILENO;
	if (!head)
		return ;
	while (head)
	{
		if (head->sep_type == 1)
		{
			head = head->next;
			n->outfile = redirection_out(head->command);
			if (n->outfile == -1)
				return ;
		}
		else if (head->sep_type == 2)
		{
			head = head->next;
			n->infile = redirection_in(head->command);
			if (n->infile == -1)
				return ;
		}
		else if (head->sep_type == 3)
		{
			head = head->next;
			n->outfile = redirection_append(head->command);
		}
		else if (head->sep_type == 5)
		{
			head = head->next;
			exec_val->flag = 1;
			n->infile = here_doc(head->command);
		}
		else if (head->type == 'W')
		{
			i = 0;
			current = head;
			while (current && current->type == 'W')
			{
				current = current->next;
				i++;
			}
			len = i;
			i = 0;
			n->command = malloc(sizeof(char *) * (len + 1));
			n->command[len] = NULL; 
			while (head && i < len)
			{
				n->command[i] = ft_strdup(head->command);
				if (i < len - 1)
					head = head->next;
				i++;
			}
		}
		else if (head->sep_type == 4)
		{
			n->next = malloc(sizeof(t_exec));
			n->next->infile = STDIN_FILENO;
			n->next->outfile = STDOUT_FILENO;
			n = n->next;
		}
		if (head)
			head = head->next;
		s++;
	}
	n->next = NULL;
	if (((n->command && s < 2) && (*list)->sep_type == 5) \
	|| (((*list)->sep_type == 1 || (*list)->sep_type == 3 \
	|| (*list)->sep_type == 2) && s < 2))
		return ;
	else 
	{
		execute_cmd(exec_val, envp);
		free_list_exe(&exec_val);
	}
}
