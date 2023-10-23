/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:58:11 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/21 10:04:03 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit(char *p)
{
	int	i;

	i = 0;
	if (p[i] == '-' || p[i] == '+' || (p[i] >= '0' && p[i] <= '9'))
		i++;
	while (p[i] && (p[i] >= '0' && p[i] <= '9'))
		i++;
	if (!p[i])
		return (0);
	return (-1);
}

void	exit_command(char **command)
{
	int	ex;
	int	i;

	i = 0;
	while (command[i])
		i++;
	if (command[1])
	{
		if (ft_atoi(command[1]) < 0)
			exit(156);
	}
	if (i > 2)
	{
		if (ft_isdigit(command[1][0]))
		{
			ft_putstr_fd(" too many arguments\n", 2);
			exit(1);
		}
		else 
			ft_putstr_fd(" too many arguments\n", 2);
		return ;
	}
	exit_norm(command, &ex);
}

int	exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

void	exit_norm(char **command, int *ex)
{
	if (!command[1])
		exit(0);
	else if (check_exit(command[1]) == -1)
	{
		ft_putstr_fd(" numeric argument required\n", 2);
		exit(255);
	}
	*ex = ft_atoi(command[1]);
	exit(*ex);
}
