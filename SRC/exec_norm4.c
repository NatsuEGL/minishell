/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_norm4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 08:05:52 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/18 09:13:58 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_norm4(t_list **head, t_exec **n)
{
	(*head) = (*head)->next;
	(*n)->infile = redirection_in((*head)->command);
	if ((*n)->infile == -1)
		return ;
}

void	exec_norm5(t_list **head, t_exec **n)
{
	(*head) = (*head)->next;
	(*n)->outfile = redirection_append((*head)->command);
}

void	exec_norm6(t_list **head, t_exec **n, t_exec **exec_val)
{
	(*head) = (*head)->next;
	(*exec_val)->flag = 1;
	(*n)->infile = here_doc((*head)->command);
}

void	exec_norm7(t_exec **n)
{
	(*n)->next = malloc(sizeof(t_exec));
	(*n)->next->infile = STDIN_FILENO;
	(*n)->next->outfile = STDOUT_FILENO;
	(*n) = (*n)->next;
}

int	exec_norm8(t_exec **n, t_list **list, int s)
{
	(*n)->next = NULL;
	if ((((*n)->command && s < 3) && (*list)->sep_type == 5) \
	|| (((*list)->sep_type == 1 || (*list)->sep_type == 3 \
	|| (*list)->sep_type == 2) && s < 2))
		return (1);
	else
		return (0);
}
