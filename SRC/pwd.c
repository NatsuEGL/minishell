/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 09:06:15 by aamhal            #+#    #+#             */
/*   Updated: 2023/09/24 11:54:50 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pwd_command(t_list *tmp, t_env **env, int fd)
{
	if (pwd_lc(tmp->command) == -1)
		return ;
	char *path = check_env(ft_strdup("PWD"),env);
	ft_putstr_fd(path,fd);
	ft_putchar_fd('\n',fd);
}

int  pwd_lc(char *p)
{
	int i = 0;
	while(p[i])
	{
		if (p[i] >= 'A' && p[i] <= 'Z')
			p[i] = p[i] + 32;
		i++;
	}
	if (!ft_strcmp(p, "pwd"))
		return (0);
	return (-1);
}
