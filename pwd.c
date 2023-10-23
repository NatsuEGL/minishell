/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 09:06:15 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/20 15:38:02 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_command(char *command, t_env **env, int fd)
{
	char	path[1024];

	if (!command)
		return ;
	if (pwd_lc(command) == -1)
		return ;
	if (getcwd(path, sizeof(path)) != NULL)
		ft_putstr_fd(path, fd);
	else
	{
		(*env)->es = 1;
		write(2, "error\n", 6);
	}
	write(1, "\n", 1);
}

int	pwd_lc(char *p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (p[i] >= 'A' && p[i] <= 'Z')
			p[i] = p[i] + 32;
		i++;
	}
	if (!ft_strcmp(p, "pwd"))
		return (0);
	return (-1);
}
