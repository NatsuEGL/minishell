 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:17:31 by aamhal            #+#    #+#             */
/*   Updated: 2023/09/20 11:16:14 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void echo_command(t_list **tmp, int fd)
{
	int f = 0;
	
	(*tmp) = (*tmp)->next;
	if (!check_echo_n((*tmp)->command))
	{
		(*tmp) = (*tmp)->next;
		while(*tmp)
		{
			ft_putstr_fd((*tmp)->command,fd);
			if ((*tmp)->next)
				ft_putchar_fd(' ', fd);	
			(*tmp) = (*tmp)->next;

		}
	}
	else
	{
		f = 1;
		while(*tmp)
		{
			ft_putstr_fd((*tmp)->command, fd);
			ft_putchar_fd(' ', fd);	
			(*tmp) = (*tmp)->next;
		}
	}
	if (f == 1)
		ft_putchar_fd('\n', fd);
}

int check_echo_n(char *str)
{
	int i = 0;

	if (str[i] != '-')
		return (-1);
	i++;
	while(str[i])
	{
		if (str[i] != 'n')
			return (-1);
		i++;
	}
	return (0);
}