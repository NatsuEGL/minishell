/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 09:06:15 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/11 22:55:24 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pwd_command(char *command, t_env **env, int fd)
{
    char    *path;

    if (pwd_lc(command) == -1)
        return ;
    path = check_env(ft_strdup("PWD"), env);
    ft_putstr_fd(path, fd);
    ft_putchar_fd('\n', fd);
    free(path);
}

int    pwd_lc(char *p)
{
    int    i;

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