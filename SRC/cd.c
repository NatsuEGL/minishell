/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 08:41:03 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/11 21:49:49 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_cdback(char *p)
{
    char **sp =ft_split(p, '/');
    int i = 0;
    int count = 0;
    while(sp[i])
    {
        if (!strcmp(sp[i],".."))
            count++;
        i++;
    }
    return (count);
}


void    cd_command(char **command, t_env **env)
{
    int i;
    if (!command[1])
        cd_home(env);
    else if (command[1] && !ft_strncmp(command[1], "..", 2))
    {
        if (ft_strlen(command[1]) == 2 || command[1][2] == '/')
        {
            i = count_cdback(command[1]);
            while(i--)
                cd_back(env);       
        }
    }
    else if (command[1])
        cd_next(command[1], env);
}

void    cd_home(t_env **env)
{
    char    *home;
    t_env    *tmp;
    char    *path;
    size_t    size;
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
    if (opwd[0] == '\0')
    {
        free(opwd);
        opwd = ft_strdup("/");
    }
    printf("|%s|\n",opwd);
    size = 0;
    if (access(opwd, F_OK) == -1)
    {
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