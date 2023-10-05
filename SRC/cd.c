/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 08:41:03 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/05 21:25:39 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    cd_command(char **command, t_env **env)
{
    if (!command[1])
        cd_home(env);
    else if (command[1] && !ft_strcmp(command[1], ".."))
        cd_back(env);
    else if (command[1])
        cd_next(command[1], env);
}

void    cd_home(t_env **env)
{
    char    *home;
    t_env    *tmp;
    char    *path;
    size_t    size;
printf("hi\n");
    home = check_env(ft_strdup("HOME"), env);
    tmp = (*env);
    path = NULL;
    size = 0;
    if (access(home, F_OK) == -1)
    {
        perror("access");
        return ;
    }
    if (chdir(home) != 0) 
    {
        perror("chdir");
        return ;
    }
    while (tmp)
    {
        if (!ft_strcmp(ft_strdup("OLDPWD"), tmp->c))
            tmp->v = check_env(ft_strdup("PWD"), env);
        tmp = tmp->next;
    }
    tmp = *env;
    if (getcwd(path, size) != NULL)
    {
        while (tmp)
        {
            if (!ft_strcmp(ft_strdup("PWD"), tmp->c))
                tmp->v = check_env(ft_strdup("HOME"), env);
            tmp = tmp->next;
        }
    }
}

void    cd_back(t_env **env)
{
    t_env    *envp;
    char    *path;
    char    *opwd;
    size_t    size;

    envp = (*env);
    path = NULL;
    opwd = ft_path(env);
    size = 0;
    if (access(opwd, F_OK) == -1)
    {
        perror("access");
        return ;
    }
    if (chdir(opwd) != 0)
    {
        perror("chdir");
        return ;
    }
    while (envp)
    {
        if (!ft_strcmp(ft_strdup("OLDPWD"), envp->c))
        {
            envp->v = check_env(ft_strdup("PWD"), env);
        }
        envp = envp->next;
    }
    envp = *env;
    if (getcwd(path, size) != NULL)
    {
        while (envp)
        {
            if (!ft_strcmp(ft_strdup("PWD"), envp->c))
                envp->v =ft_strjoin(ft_strdup(""), opwd);
            envp = envp->next;
        }
    }
}
void    cd_next(char *command ,t_env **env)
{
    t_env    *envp;
    char    *path;
    size_t    size;
    envp = (*env);
    path = NULL;
    size = 0;
    if (access(command, F_OK) == -1)
    {
        perror("access");
        return ;
    }
    if (chdir(command) != 0)
    {
        perror("chdir");
        return ;
    }
    while (envp)
    {
        if (!ft_strcmp("OLDPWD", envp->c))
            envp->v = check_env(ft_strdup("PWD"), env);
        envp = envp->next;
    }
    envp = *env;
    if (getcwd(path, size) != NULL)
    {
        while (envp)
        {
            if (!ft_strcmp(ft_strdup("PWD"), envp->c))
            {
                envp->v = ft_strjoin(envp->v, ft_strdup("/"));
                envp->v = ft_strjoin(envp->v, ft_strdup(command));
            }
            envp = envp->next;
        }
    }
}

char    *ft_path(t_env **env)
{
    char    *path;
    char    *p; 
    int        i;
    int        j;
    char    *x;

    path = check_env(ft_strdup("PWD"), env);
    p = ft_strrchr(path, '/'); 
    i = ft_strlen(path);
    j = ft_strlen(p);
    x = ft_substr(path, 0, (i - j));
    free(path);
    return (x);
}