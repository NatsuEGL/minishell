/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 08:41:03 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/15 20:54:06 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_command(char **command, t_env **env)
{
	int	i;

	if (!command[1])
		cd_home(env);
	else if (command[1] && !ft_strcmp(command[1], "/"))
		cd_slash(env);
	else if (command[1] && !ft_strncmp(command[1], "..", 2))
	{
		if (ft_strlen(command[1]) == 2 || command[1][2] == '/')
		{
			i = count_cdback(command[1]);
			while (i--)
				cd_back(env);
		}
	}
	else if (command[1])
		cd_next(command[1], env);
}

void	cd_home(t_env **env)
{
	char	*home;
	t_env	*tmp;
	char	*path;
	size_t	size;

	home = check_env(ft_strdup("HOME"), env);
	tmp = (*env);
	path = NULL;
	size = 0;
	cd_error(home, 1);
	cd_next_env(tmp, env);
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

void	cd_back(t_env **env)
{
	t_env	*envp;
	char	*path;
	char	*opwd;
	size_t	size;

	envp = (*env);
	path = NULL;
	opwd = ft_path(env);
	if (opwd[0] == '\0')
		opwd = cd_back_free(opwd);
	size = 0;
	cd_error(opwd, 0);
	cd_next_env(envp, env);
	envp = *env;
	if (getcwd(path, size) != NULL)
	{
		while (envp)
		{
			if (!ft_strcmp(ft_strdup("PWD"), envp->c))
				envp->v = ft_strjoin(ft_strdup(""), opwd);
			envp = envp->next;
		}
	}
}

void	cd_next(char *command, t_env **env)
{
	t_env	*envp;
	char	*path;
	size_t	size;

	envp = (*env);
	path = NULL;
	size = 0;
	command = last_slash(command);
	cd_error(command, 1);
	cd_next_env(envp, env);
	envp = *env;
	if (getcwd(path, size) != NULL)
	{
		while (envp)
		{
			if (!ft_strcmp(ft_strdup("PWD"), envp->c))
			{
				if (strcmp(envp->v, "/"))
					envp->v = ft_strjoin(ft_strdup(envp->v), ft_strdup("/"));
				envp->v = ft_strjoin(envp->v, ft_strdup(command));
			}
			envp = envp->next;
		}
	}
}

void	cd_next_env(t_env *envp, t_env **env)
{
	while (envp)
	{
		if (!ft_strcmp("OLDPWD", envp->c))
			envp->v = check_env(ft_strdup("PWD"), env);
		envp = envp->next;
	}
}
