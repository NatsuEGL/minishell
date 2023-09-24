/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:53:42 by akaabi            #+#    #+#             */
/*   Updated: 2023/09/22 09:33:18 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void builting(t_list **list, t_env **envp)
{
    t_list *tmp;
    
    tmp = *list;
	if (tmp && !ft_strcmp(tmp->command, "export"))
	{
		tmp = tmp->next;
		while (tmp)
		{
			update_or_add_env(envp, tmp->command);
			tmp = tmp->next;
		}
	}
	if (tmp && !ft_strcmp(tmp->command, "unset"))
	{
		tmp = tmp->next;
		if (!ft_strcmp(tmp->command, "_"))
			return ;
		while (tmp)
		{
			delete_from_env(envp, tmp->command);
			tmp = tmp->next;
		}
	}
	if (tmp && !ft_strcmp(tmp->command, "env"))
		print_nodes(*envp);
    check_echo(list,1);
    ft_free_lst(list);
}

void read_from_pipe(int pipes, t_env **env, t_list **list)
{
	char *buffer;
	int i = 0;

	buffer = malloc(sizeof(char) * 256);
	i = read(pipes, buffer, 255);
	if (i > 0)
	{
		// there is a pipe
		buffer[i] = '\0';
		printf("ok here is the pipe sir : %s\n", buffer);
		printf("hana l9itha\n");
	}
	else
	{
		// there is no pipe
	char *path_var = check_env(ft_strdup("PATH"), env);
	char **executable_info = check_path_for_command(path_var, (*list)->command);
    if (executable_info != NULL)
	{
        printf("Executing command: %s\n", executable_info[0]);
        execute_command((const char *const *)executable_info);
        free(executable_info);
    } else
	{
        printf("Command '%s' not found in PATH.\n", (*list)->command);
    }
	}
	free(buffer);
}

void open_pipe(t_list **list, t_env **envp)
{
	(void)envp;
	// (void)list;
	int pipes[2];
	pid_t pid;

	if (pipe(pipes) == -1)
	{
		perror("error\n");
		exit (1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("error\n");
		exit (1);
	}
	if (pid == 0)
	{
		close(pipes[1]);
		dup2(pipes[0], STDIN_FILENO);
		read_from_pipe(STDIN_FILENO, envp, list);
		close(pipes[0]);
		exit(0);
	}
	else{
		close(pipes[0]);
		t_list *tmp;
		
		tmp = (*list);
		while (tmp)
		{
			if (tmp->command[0] == '|')
			{
        		ft_putstr_fd(tmp->command, pipes[1]);
				break;
			}
			tmp = tmp->next;
		}
        close(pipes[1]);
        wait(NULL);
	}
}

char* concatenate_path_len(char *directory, size_t dir_length, const char *command)
{
    // Calculate dir len
    int total_length = dir_length + ft_strlen(command) + 2;
    char *path = (char *)malloc(total_length);
    if (path == NULL) {
        perror("malloc");
        exit(1);
    }
    // Copy the directory
    ft_strncpy(path, directory, dir_length);
    path[dir_length] = '/';
    strcpy(path + dir_length + 1, command);
    return (path);
}

char** check_path_for_command(char *path_var, char *command)
{
    char *path_ptr = path_var;

    while (*path_ptr != '\0')
	{
        // end of my dir
        char *end_ptr = path_ptr;
        while (*end_ptr != '\0' && *end_ptr != ':')
            end_ptr++;
        // Calculate dir len
        size_t dir_length = end_ptr - path_ptr;
        //appending the command
        char *full_path = concatenate_path_len(path_ptr, dir_length, command);
        if (access(full_path, X_OK) == 0)
		{
            char **executable_info = (char **)malloc(2 * sizeof(char *));
            if (executable_info == NULL) {
                perror("malloc");
                free(full_path);
                exit(1);
            }
            executable_info[0] = full_path;
            executable_info[1] = NULL;
            return executable_info;
        }
        free(full_path);
        // Move to the next
        if (*end_ptr == ':')
            path_ptr = end_ptr + 1;
		else
            break;  //end of the PATH
    }
    return (NULL);
}

void execute_command(const char *const *executable_info)
{
    // Execute the command using execve
    if (execve(executable_info[0], (char *const *)executable_info, NULL) == -1)
	{
        perror("execve");
        exit(1);
    }
}

char* find_path(t_env *envp)
{
    t_env *current = envp;

    while (current != NULL)
	{
        if (strcmp(current->c, "PATH=") == 0)
            return current->v;
        current = current->next;
    }
    return (NULL);
}
