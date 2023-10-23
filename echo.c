/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:25:48 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/21 11:56:25 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_command(char **command, int fd, t_env **env)
{
	int	i;

	i = 1;
	if (!command[1])
		return ;
	if (!ft_strcmp(command[1], "$?"))
	{
		ft_putnbr_fd((*env)->es, 1);
		ft_putchar_fd('\n', fd);
		(*env)->es = 0;
		return ;
	}
	if (!check_echo_n(command[1]))
	{
		i++;
		while (command[i])
		{
			ft_putstr_fd(command[i], fd);
			if (command[i + 1])
				ft_putchar_fd(' ', fd);
			i++;
		}
	}
	else 
		echo_norm(command, fd);
}

int	check_echo_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (-1);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (-1);
		i++;
	}
	return (0);
}

void	echo_norm(char **command, int fd)
{
	int	f;
	int	i;

	i = 1;
	f = 1;
	while (command[i])
	{
		ft_putstr_fd(command[i], fd);
		if (command[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (f == 1)
		ft_putchar_fd('\n', fd);
}
