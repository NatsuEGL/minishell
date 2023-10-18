/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:34:29 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/15 20:55:34 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cdback(char *p)
{
	char	**sp;
	int		i;
	int		count;

	sp = ft_split(p, '/');
	i = 0;
	count = 0;
	while (sp[i])
	{
		if (!strcmp(sp[i], ".."))
			count++;
		i++;
	}
	return (count);
}

char	*ft_path(t_env **env)
{
	char	*path;
	char	*p; 
	int		i;
	int		j;
	char	*x;

	path = check_env(ft_strdup("PWD"), env);
	p = ft_strrchr(path, '/'); 
	i = ft_strlen(path);
	j = ft_strlen(p);
	x = ft_substr(path, 0, (i - j));
	free(path);
	return (x);
}

void	cd_slash(t_env **env)
{
	t_env	*envp;
	char	*path;
	size_t	size;

	envp = (*env);
	path = NULL;
	size = 0;
	cd_error("/", 1);
	cd_next_env(envp, env);
	envp = *env;
	if (getcwd(path, size) != NULL)
	{
		while (envp)
		{
			if (!ft_strcmp(ft_strdup("PWD"), envp->c))
			{
				free(envp->v);
				envp->v = ft_strdup("/");
			}
			envp = envp->next;
		}
	}
}

char	*last_slash(char *p)
{
	int		i;
	int		len;
	char	*x;

	i = 0;
	len = ft_strlen(p);
	x = malloc(len);
	x[len - 1] = '\0';
	while (len - 1 > i)
	{
		x[i] = p[i];
		i++;
	}
	free(p);
	return (x);
}

void	cd_error(char *p, int f)
{
	if (access(p, F_OK) == -1)
	{
		if (f == 1)
			perror("access");
		return ;
	}
	if (chdir(p) != 0)
	{
		perror("chdir");
		return ;
	}
}
