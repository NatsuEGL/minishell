/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:53:42 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/11 22:57:42 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void builting(t_exec **list, t_env **envp, int data)
{
	t_exec *tmp;
	char *path;

	tmp = (*list);
	while(tmp)
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
			path = check_env(ft_strdup("PATH"),envp);
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
			exit_command(tmp->command,data);

		// makaynsh null f next
		tmp= tmp->next;
	}
}
//excuting_multpile_pipes
	//checking_if_bulting
		//flag == 1
	//if flag
		//9awd
	

// void last_execution(int pipes, t_env **env, t_list **list)
// {
// 	//checking_if_bulting
// 	char *buffer;
// 	int i = 0;
// 	// (void)env;
// 	// (void)list;

// 	buffer = malloc(sizeof(char) * 256);
// 	i = read(pipes, buffer, 255);
// 	if (i > 0)
// 	{
// 		// there is a pipe
// 		buffer[i] = '\0';
// 		printf("here is the pipe %s\n",buffer);
// 		// exec_command(list,env);
// 	}
// 	else
// 	{
// 		// there is no pipe
// 		printf("wa7ed\n");
// 		exec_command(list,env);
// 	}
// 	free(buffer);
// }

// void open_pipe(t_list **list, t_env **envp)
// {
// 	(void)envp;
// 	// (void)list;
// 	int pipes[2];
// 	pid_t pid;

// 	if (pipe(pipes) == -1)
// 	{
// 		perror("error\n");
// 		exit (1);
// 	}
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("error\n");
// 		exit (1);
// 	}
// 	if (pid == 0)
// 	{
// 		close(pipes[1]);
// 		dup2(pipes[0], STDIN_FILENO);
// 		last_execution(STDIN_FILENO, envp, list);
// 		close(pipes[0]);
// 		exit(0);
// 	}
// 	else{
// 		close(pipes[0]);
// 		t_list *tmp;
		
// 		tmp = (*list);
// 		while (tmp)
// 		{
// 			if (tmp->command[0] == '|')
// 			{
//         		ft_putstr_fd(tmp->command, pipes[1]);
// 				break;
// 			}
// 			tmp = tmp->next;
// 		}
//         close(pipes[1]);
//         wait(NULL);
// 	}
// }

char* concatenate_path_len(char *directory, size_t dir_length, char *command)
{
    // Calculate dir len
    int full_len;
    char *path;

	full_len = dir_length + ft_strlen(command) + 2;
	path = malloc(full_len);
    if (path == NULL) {
        perror("malloc");
        exit(1);
    }
    // Copy the directory
    ft_strncpy(path, directory, dir_length);
    path[dir_length] = '/';
	//forbidden_func
    ft_strcpy(path + dir_length + 1, command);
	// printf("%s")
    return (path);
}

char** check_path_for_command(char *path_var, char *command)
{
    char *path;
	char *end;
	int dir_length;
	char *full_path;
	char **executable_info;

	path = path_var;
    while (*path != '\0')
	{
        // end of my dir
        end = path;
        while (*end != '\0' && *end != ':')
            end++;
        // Calculate dir len
        dir_length = end - path;
        //appending the command
        full_path = concatenate_path_len(path, dir_length, command);
        if (access(full_path, X_OK) == 0)
		{
            executable_info = malloc(2 * sizeof(char *));
            if (executable_info == NULL)
			{
                perror("malloc");
                free(full_path);
                exit(1);
            }
            executable_info[0] = full_path;
            executable_info[1] = NULL;
			free(full_path);
            return (executable_info);
        }
        free(full_path);
        // Move to the next
        if (*end == ':')
            path = end + 1;
		else
            break;  //end of the PATH
    }
    return (NULL);
}

void execute_command(char **executable_info)
{
    // Execute the command using execve
    if (execve(*executable_info, executable_info, NULL) == -1)
	{
        perror("execve");
        exit(1);
    }
}

//exec_part()

// int	redirection_in(char *file)
// {
// 	int fd = open(file, O_RDONLY, 0777);
// 	if (fd == -1)
// 		return -1;
// 	return (fd);
// }

// int	redirection_out(char *file)
// {
// 	int fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
// 	if (fd == -1)
// 		return -1;
// 	return (fd);
// }

// int	redirection_append(char *file)
// {
// 	int fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
// 	if (fd == -1)
// 		return -1;
// 	return (fd);
// }

// int	here_doc(char *Delim, t_exec *exec_val)
// {
// 	int fd[2];
// 	int status;
// 	char *cmd;
// 	pid_t pid;
// 	(void)exec_val;

	
// 	if (pipe(fd) == -1)
// 		return (-1);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		while(1)
// 		{
// 			cmd = readline("Heredoc> ");
// 			if (!ft_strcmp(cmd, Delim))
// 			{
// 				free(cmd);
// 				exit(0);
// 			}
// 			// if (exec_val->infile != STDIN_FILENO)
// 			// {
// 			// 	dup2(exec_val->infile, STDIN_FILENO);
// 			// 	close(exec_val->infile);	
// 			// }
// 			// if (exec_val->outfile == STDOUT_FILENO && exec_val->flag == 1)
// 			// {
// 			// 	dup2(exec_val->outfile, STDOUT_FILENO);
// 			// 	ft_putstr_fd(cmd, exec_val->outfile);
// 			// 	write(exec_val->outfile, "\n", 1);
// 			// 	free(cmd);
// 			// }
// 			// else
// 			// {
// 				ft_putstr_fd(cmd, fd[1]);
// 				write(fd[1], "\n", 1);
// 				free(cmd);
// 			// }
// 		}
// 	}
// 	waitpid(pid, &status, 0);
// 	//signals
// 				// close(exec_val->outfile);
// 	close(fd[1]);
// 	return(fd[0]);
// }

// int	list_size(t_exec *exec_val)
// {
// 	t_exec *head;
	
// 	int size = 0;
// 	if (!exec_val)
// 		return (0);
// 	head = exec_val;
// 	while(head)
// 	{
// 		size++;
// 		head = head ->next;
// 	}
// 	return (size);
// }

// char *searching_path(char *command, t_env **envp)
// {
// 	char *path = check_env(ft_strdup("PATH"), envp);
// 	char **path_splied = check_path_for_command(path, command);
// 	if (!path_splied)
// 	{
// 		printf("command not found\n");
// 		exit(0) ;
// 	}
// 	return(path_splied[0]);
// }

// int	Builting_check(char *command)
// {
// 	if (!ft_strcmp(command, "env")
// 		|| !ft_strcmp(command, "export")
// 		|| !ft_strcmp(command, "unset")
// 		|| !ft_strcmp(command, "echo")
// 		|| !ft_strcmp(command, "cd")
// 		|| !ft_strcmp(command, "pwd")
// 		|| !ft_strcmp(command, "exit"))
// 		return (0);
// 	return (1);
// }

// void	simple_command(t_exec *exec_val, t_env **envp)
// {
// 	pid_t pid ;
// 	char *path;

// 	pid = fork();
// 	if (pid == -1)
// 		return ;
// 	if (pid == 0)
// 	{
// 		if (exec_val->infile != STDIN_FILENO)
// 		{
// 			dup2(exec_val->infile, STDIN_FILENO);
// 			close(exec_val->infile);	
// 		}
// 		if (exec_val->outfile != STDOUT_FILENO)
// 		{
// 			dup2(exec_val->outfile, STDOUT_FILENO);
// 			close(exec_val->outfile);
// 		}
// 		path = searching_path(exec_val->command[0], envp);
// 		free(exec_val->command[0]);
// 		exec_val->command[0] = ft_strdup(path);
// 		free(path);
// 		execve(exec_val->command[0], exec_val->command, (*envp)->envir);
// 	}
// 	waitpid(pid, NULL, 0);
// 	if (exec_val->infile != STDIN_FILENO)
// 		close(exec_val->infile);
// 	if (exec_val->outfile != STDOUT_FILENO)
// 		close(exec_val->outfile);
// 	return ;
// }

// int size_of_pipe(char **command)
// {

//  	int count = 0;
//     char **p = command;
// 	char *p1 = NULL;
//     while (*p != NULL) 
// 	{
// 		p1 = *p;
//         while (*p1 != '\0') 
// 		{
//             if (*p1 == '|')
//                 count++;
//             p1++;
//         }
//         p++;
//     }
//     return count;
// }


// pid_t young_child(t_exec *exec_val)
// {
// 	if (exec_val->infile != STDIN_FILENO)
// 	{
// 		dup2(exec_val->infile, STDIN_FILENO);
// 		close(exec_val->infile);
// 	}
// 	if (exec_val->outfile != STDIN_FILENO)
// 	{
// 			dup2(exec_val->outfile, STDIN_FILENO);
// 			close(exec_val->outfile);
// 	}
// }

// pid_t midle_child(t_exec *exec_val)
// {
	
// }

// pid_t older_child(t_exec *exec_val)
// {
	
// }

// pid_t exec_first_command(t_exec *exec_val, t_env **envp)
// {
// 	int fd[2];
// 	pid_t pid;
// 	char *path;

// 	if (pipe(fd) == -1)
// 	{
// 		perror("pipe");
// 		exit(1);
// 	}
	
// 	pid = fork();

// 	if (pid == -1)
// 	{
// 		perror("pid");
// 		exit (1);
// 	}

// 	if (pid == 0)
// 	{
// 		// child process
// 		if (exec_val->infile != STDIN_FILENO)
// 		{
// 			dup2(exec_val->infile, STDIN_FILENO);
// 			close(exec_val->infile);	
// 		}
// 		if (exec_val->outfile != STDOUT_FILENO)
// 		{
// 			dup2(exec_val->outfile, STDOUT_FILENO);
// 			close(exec_val->outfile);
// 		}
// 		else	
// 		{
// 			dup2(fd[1],STDOUT_FILENO);
// 			close(fd[0]);
// 			close(fd[1]);
// 		}
// 		path = searching_path(exec_val->command[0], envp);
// 		free(exec_val->command[0]);
// 		// dprintf(2, "execute %s", *exec_val->command)
// 		exec_val->command[0] = ft_strdup(path);
// 		free(path);
// 		execve(exec_val->command[0], exec_val->command, (*envp)->envir);
// 		exit(1);
// 	}
// 	dup2(fd[0], STDIN_FILENO);
// 	close(fd[0]);
// 	close(fd[1]);
// 	return (pid);
// }

// pid_t exec_last_command(t_exec *exec_val, t_env **envp)
// {
// 	pid_t pid;
// 	char *path;
	
// 	pid = fork();

// 	if (pid == -1)
// 	{
// 		perror("pid");
// 		exit (1);
// 	}

// 	if (pid == 0)
// 	{
// 		// child process 2
// 		if (exec_val->infile != STDIN_FILENO)
// 		{
// 			dup2(exec_val->infile, STDIN_FILENO);
// 			close(exec_val->infile);	
// 		}
// 		// else	
// 		// {
// 		// 	dup2(fd[0],STDIN_FILENO);
// 		// 	close(fd[1]);
// 		// 	close(fd[0]);
// 		// }
// 		if (exec_val->outfile != STDOUT_FILENO)
// 		{
// 			dup2(exec_val->outfile, STDOUT_FILENO);
// 			close(exec_val->outfile);
// 		}
		
// 		path = searching_path(exec_val->command[0], envp);
// 		free(exec_val->command[0]);
// 		exec_val->command[0] = ft_strdup(path);
// 		free(path);
// 		execve(exec_val->command[0], exec_val->command, (*envp)->envir);
// 	}
// 	// close(fd[0]);
// 	// close(fd[1]);
// 	return (pid);
// }

// int **make_fd(int n)
// {
// 	int i;
// 	int **fd;
	
// 	i = 0;
// 	fd = malloc(sizeof(int *) * (n));
// 	while(i < n - 1)
// 	{
// 		fd[i] = malloc(sizeof(int) * 2);
// 		i++;
// 	}
// 	fd[i] = NULL;
// 	return (fd);
// }

// pid_t first_child(t_exec *exec_val, t_env **envp, int **fd)
// {
// 	pid_t pid;
// 	char *path;
// 	size_t i;

// 	pid = fork();
// 	i = 0;
// 	if (pid == -1)
// 	{
// 		perror(":pid 1st child:");
// 		exit(1);
// 	}
// 	else if (pid == 0)
// 	{
// 	// 	if (exec_val->flag)
// 	// 	{
// 	// 		exec_val->flag = 0;
// 	// 		exit (0);
// 	// 	}
// 		if (exec_val->infile != STDIN_FILENO && exec_val->flag == 0)
// 		{
// 			dup2(exec_val->infile, STDIN_FILENO);
// 			close(exec_val->infile);
// 		}
// 		if (exec_val->outfile != STDOUT_FILENO)
// 		{
// 			dup2(exec_val->outfile, STDOUT_FILENO);
// 			close(exec_val->outfile);
// 		}
// 		else
// 			dup2(fd[0][1], STDOUT_FILENO);
// 		while(fd[i])
// 		{
// 			close(fd[i][0]);
// 			close(fd[i][1]);
// 			i++;
// 		}
// 		if (!Builting_check(exec_val->command[0]))
// 		{
// 			builting(&exec_val, envp, exec_val->outfile);
// 			exit (0);
// 		}
// 		path = searching_path(exec_val->command[0], envp);
// 		free(exec_val->command[0]);
// 		exec_val->command[0] = ft_strdup(path);
// 		free(path);
// 		execve(exec_val->command[0], exec_val->command, (*envp)->envir);
// 	}
// 	return(pid);
// }

// pid_t middle_child(t_exec *exec_val, t_env **envp, int **fd, size_t i)
// {
// 	pid_t pid;
// 	char *path;
// 	size_t j;

// 	pid = fork();
// 	j = 0;
// 	if (pid == -1)
// 	{
// 		perror(":pid midlle child:");
// 		exit(1);
// 	}
// 	else if (pid == 0)
// 	{
// 		// if (exec_val->flag)
// 		// {
// 		// 	exec_val->flag = 0;
// 		// }
// 		if (exec_val->infile != STDIN_FILENO)
// 		{
// 			dup2(exec_val->infile, STDIN_FILENO);
// 			close(exec_val->infile);
// 		}
// 		else
// 			dup2(fd[i - 1][0], STDIN_FILENO);
// 		if (exec_val->outfile != STDOUT_FILENO)
// 		{
// 			dup2(exec_val->outfile, STDOUT_FILENO);
// 			close(exec_val->outfile);
// 		}
// 		else
// 			dup2(fd[i][1], STDOUT_FILENO);
// 		while(fd[j])
// 		{
// 			close(fd[j][0]);
// 			close(fd[j][1]);
// 			j++;
// 		}
// 		if (!Builting_check(exec_val->command[0]))
// 		{
// 			builting(&exec_val, envp, exec_val->outfile);
// 			exit (0);
// 		}
// 		path = searching_path(exec_val->command[0], envp);
// 		free(exec_val->command[0]);
// 		exec_val->command[0] = ft_strdup(path);
// 		free(path);
// 		execve(exec_val->command[0], exec_val->command, (*envp)->envir);
// 	}
// 	return(pid);
// }

// pid_t last_child(t_exec *exec_val , t_env **envp, int **fd, int n)
// {
// 	pid_t pid;
// 	char *path;
// 	size_t j;

// 	pid = fork();
// 	j = 0;
// 	if (pid == -1)
// 	{
// 		perror(":pid last child:");
// 		exit(1);
// 	}
// 	else if (pid == 0)
// 	{
// 		if (exec_val->flag)
// 		{
// 			exec_val->flag = 0;
// 			exit (0);
// 		}
// 		if (exec_val->infile != STDIN_FILENO)
// 		{
// 			dup2(exec_val->infile, STDIN_FILENO);
// 			close(exec_val->infile);
// 		}
// 		else
// 			dup2(fd[n][0], STDIN_FILENO);
// 		if (exec_val->outfile != STDOUT_FILENO)
// 		{
// 			dup2(exec_val->outfile, STDOUT_FILENO);
// 			close(exec_val->outfile);
// 		}
// 		while(fd[j])
// 		{
// 			close(fd[j][0]);
// 			close(fd[j][1]);
// 			j++;
// 		}
// 		if (!Builting_check(exec_val->command[0]))
// 		{
// 			builting(&exec_val, envp, exec_val->outfile);
// 			exit (0);
// 		}
// 		path = searching_path(exec_val->command[0], envp);
// 		free(exec_val->command[0]);
// 		exec_val->command[0] = ft_strdup(path);
// 		free(path);
// 		execve(exec_val->command[0], exec_val->command, (*envp)->envir);
// 	}
// 	return(pid);	
// }

// void free_double(int **fd)
// {
// 	size_t i;

// 	i = 0;
// 	while(fd[i])
// 	{
// 		free(fd[i]);
// 		i++;
// 	}
// 	free(fd);
// }

// void multiple_command(t_exec *exec_val , t_env **envp)
// {
// 	int n = list_size(exec_val); // how many pipes that i have if it's n - 1
// 	pid_t pid[3];
// 	int	**fd;
// 	int i;
// 	int j;

// 	i = 1;
// 	j = 0;
// 	fd = make_fd(n);
// 	while(fd[j])
// 	{
// 		if (pipe(fd[j]) == -1)
// 		{
// 			perror(":pipe fd:");
// 			exit(0);
// 		}
// 		j++;
// 	}
// 	pid[0] = first_child(exec_val, envp, fd);
// 	exec_val = exec_val->next;
// 	while(i < n - 1)
// 	{
// 		pid[1] = middle_child(exec_val, envp, fd, i);
// 		exec_val = exec_val->next;
// 		i++;
// 	}
// 	pid[2] = last_child(exec_val, envp, fd, (i - 1));
// 	i = 0;
// 	while(fd[i])
// 	{
// 		close(fd[i][0]);
// 		close(fd[i][1]);
// 		i++;
// 	}
// 	waitpid(pid[0], NULL, 0);
// 	waitpid(pid[1], NULL, 0);
// 	waitpid(pid[2], NULL, 0);
// 	free_double(fd);
// 	return ;
// }

void	execute_cmd(t_exec *exec_val, t_env **envp)
{
	if (list_size(exec_val) > 1)
	{
		multiple_command(exec_val, envp);
	}
	else
	{
	// 	puts("hehe\n");
	// exit(0);
		 if (!Builting_check(exec_val->command[0]))
		{
			builting(&exec_val, envp, exec_val->outfile);
			return ;
		}
		else
			simple_command(exec_val, envp);		
	}
}

// void free_list_exe(t_exec **list)
// {
// 	if (!(*list))
// 		return ;
// 	if ((*list)->next)
// 		free_list_exe(&(*list)->next);
// 	free((*list)->command);
// 	free(*list);
// 	*list = NULL;
// }

void execution_part(t_list **list, t_env **envp)
{
	t_list *head;
	t_list *current;
	int i = 0;
	int len = 0;
	t_exec *n;
	t_exec *exec_val;	

	head = *list;
	exec_val = malloc(sizeof(t_exec));
	n = exec_val;
	n->infile = STDIN_FILENO;
	n->outfile = STDOUT_FILENO;
	if (!head)
		return ;
		int s = 0;
	while(head)
	{
		if (head->sep_type == 1)
		{
			head = head->next;
			n->outfile = redirection_out(head->command);
			//protection
			if (n->outfile == -1)
				return ;
		}
		else if (head->sep_type == 2)
		{
			head = head->next;
			n->infile = redirection_in(head->command);
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
			while(current && current->type == 'W')
			{
				current = current->next;
				i++;
			}
			len = i;
			i = 0;
			n->command = malloc(sizeof(char *) * (len + 1));
			n->command[len] = NULL; 
			while(head && i < len)
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
	if (n->command && s < 2 && (*list)->sep_type == 5)
		return ;
	else 
	{
		execute_cmd(exec_val, envp);
		free_list_exe(&exec_val);
	}
}