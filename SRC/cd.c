/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 08:41:03 by aamhal            #+#    #+#             */
/*   Updated: 2023/09/24 11:45:06 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cd_command(t_list *tmp, t_env **env)
{	
	if (!tmp->next || tmp->next->type == 'S')
		cd_home(env);
	else if (tmp->next && !ft_strcmp(tmp->next->command,".."))
		cd_back(env);
	else if (tmp->next)
		cd_next(tmp,env);
}

void cd_home(t_env **env)
{
	char *home = check_env(ft_strdup("HOME"),env);
	t_env *tmp = (*env);
	char *path = NULL;
	size_t size = 0;
	if (access(home, F_OK) == -1) {
        perror("access");
        return ;
    }

    if (chdir(home) != 0) {
        perror("chdir");
        return ;
    }
	while (tmp)
	{
		if (!ft_strcmp(ft_strdup("OLDPWD"),tmp->c))
			tmp->v = check_env(ft_strdup("PWD"),env);
		tmp = tmp->next;
    }
	tmp = *env;
	if (getcwd(path, size) != NULL)
	{
		while(tmp)
		{
		if (!ft_strcmp(ft_strdup("PWD"),tmp->c))
			tmp->v = check_env(ft_strdup("HOME"),env);
		tmp = tmp->next;
		}
	}
}

void cd_back(t_env **env)
{
	t_env *envp = (*env);
	char *path = NULL;
	char *opwd = ft_path(env);
	size_t size = 0;

	if (access(opwd, F_OK) == -1) {
        perror("access");
        return ;
    }

    if (chdir(opwd) != 0) {
        perror("chdir");
        return ;
    }

	while (envp)
	{
		if (!ft_strcmp(ft_strdup("OLDPWD"),envp->c))
		{
			envp->v = check_env(ft_strdup("PWD"),env);
		}
		envp = envp->next;
    }
	envp = *env;
	if (getcwd(path, size) != NULL)
	{
		while(envp)
		{
			if (!ft_strcmp(ft_strdup("PWD"),envp->c))
				envp->v =ft_strjoin(ft_strdup(""),opwd);
			envp = envp->next;
		}
	}
}
void cd_next(t_list *tmp,t_env **env)
{
	t_env *envp = (*env);
	char *path = NULL;
	size_t size = 0;
	if (access(tmp->next->command, F_OK) == -1) {
        perror("access");
        return ;
    }

    if (chdir(tmp->next->command) != 0) {
        perror("chdir");
        return ;
    }

	while (envp)
	{
		if (!ft_strcmp("OLDPWD",envp->c))
			envp->v = check_env(ft_strdup("PWD"),env);
		envp = envp->next;
    }
	envp = *env;
	if (getcwd(path, size) != NULL)
	{
		while(envp)
		{
			if (!ft_strcmp(ft_strdup("PWD"),envp->c))
			{
				envp->v = ft_strjoin(envp->v,ft_strdup("/"));
				envp->v = ft_strjoin(envp->v,ft_strdup(tmp->next->command));
			}
			envp = envp->next;
		}
	}
}

char *ft_path(t_env **env)
{
	char *path = check_env(ft_strdup("PWD"),env);
	char *p = ft_strrchr(path, '/'); 
	int i = ft_strlen(path);
	int j = ft_strlen(p);
	char *x = ft_substr(path,0,i-j);
	free(path);
	return(x);
}