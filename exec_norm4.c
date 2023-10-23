/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_norm4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 08:05:52 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/23 08:43:56 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_norm4(t_list **head, t_exec **n)
{
	(*head) = (*head)->next;
	(*n)->flag3 = 1;
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
	(void)exec_val;
	(*head) = (*head)->next;
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
	(void)list;
	if (((*n)->flag == 1 && s < 2))
		return (1);
	else
		return (0);
}
