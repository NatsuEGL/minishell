/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 08:48:43 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/03 19:00:49 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    read_from_doc(t_list **list)
{
    char *del = delimiter(list);
    (*list)->buffer = readline("> ");
    if (!ft_strcmp((*list)->buffer,del))
    {
        free((*list)->buffer);
        exit(0);
    }
    close((*list)->pipes[0]);
    ft_putstr_fd((*list)->buffer,(*list)->pipes[1]);
    ft_putstr_fd("\n",(*list)->pipes[1]);
    free((*list)->buffer);
}

void    open_heredoc(t_list **list)
{
    pid_t pid;

    if (pipe((*list)->pipes) == -1)
    {
        perror("error\n");
        exit(1);
    }

    pid = fork();
    
    if (pid == -1)
    {
        perror("error\n");
        exit(1);
    }
    else if (pid == 0)
    {
        close((*list)->pipes[1]);
        while (1)
            read_from_doc(list);
    }
    wait(NULL);
    close((*list)->pipes[1]);
}

int check_heredoc(t_list **list)
{
	t_list *tmp = (*list);
	while (tmp)
	{
		if (!ft_strcmp(tmp->command,"<<"))
			return (0);
		tmp = tmp->next;
	}
	return (-1);
}