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


void echo_command(char **command, int fd)
{
    int    i = 1;
    int    f = 0;
    if (!ft_strcmp(command[1], "$?"))
    {
        ft_putnbr_fd(es,1);
        ft_putchar_fd('\n', fd);
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
    {
        f = 1;
        while (command[i])
        {
            ft_putstr_fd(command[i], fd);
            ft_putchar_fd(' ', fd);
            i++;
        }
    }
    if (f == 1)
        ft_putchar_fd('\n', fd);
}

int    check_echo_n(char *str)
{
    int    i;

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