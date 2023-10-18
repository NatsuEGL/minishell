/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:58:11 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/12 20:31:28 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit(char *p)
{
	int	i;

	i = 0;
	while (p[i] && (p[i] >= '0' && p[i] <= '9'))
		i++;
	if (!p[i])
		return (0);
	return (-1);
}

void	exit_command(char **command, int data)
{
	int	ex;
	int	i;

	i = 0;
	while (command[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("too many arguments\n", data);
		return ;
	}
	if (!command[1])
		exit(0);
	else if (check_exit(command[1]) == -1)
	{
		ft_putstr_fd("numeric argument required\n", data);
		exit(255);
	}
	ex = ft_atoi(command[1]);
	exit(ex);
}

int	exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
