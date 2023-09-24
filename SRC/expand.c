/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 08:37:36 by aamhal            #+#    #+#             */
/*   Updated: 2023/09/17 11:00:58 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_list **list, t_env **env)
{
	t_list	*tmp;
	int		i;

	tmp = *list;
	while (tmp)
	{
		i = 0;
		while (tmp->command[i])
		{
			if (tmp->command[i] == '$' && tmp->command[i + 1] == '\0')
				break ;
			if (tmp->command[i] == '$')
			{
				check_expand(tmp, env);
				break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
}

void	check_expand(t_list *tmp, t_env **env)
{
	int	i;

	i = 0;
	while (tmp->command[i])
	{
		if (tmp->command[i] == '\"' || tmp->command[i] == '\'')
		{
			separ_expland(tmp, env);
			return ;
		}
		i++;
	}
	normal_expand(tmp, env);
}

int	ft_check_ex(char *p)
{
	int	i;

	i = 0;
	while (p[i])
	{
	if (p[i] == '$' && !ft_isalnum(p[i + 1]) && p[i + 1] != '_')
		return (0);
		i++;
	}
	return (-1);
}
char	*check_env_q(char *p, t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (!ft_strcmp(p, tmp->c))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		if (ft_check_ex(p) == -1)
			return (free(p), NULL);
		p = ft_strjoin(ft_strdup("$"), p);
		return (p);
	}
	free(p);
	return (ft_strdup(tmp->v));
}
char	*check_env(char *p, t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (!ft_strcmp(p, tmp->c))
			break ;
		tmp = tmp->next;
	}
	free(p);
	if (!tmp)
		return (NULL);
	return (ft_strdup(tmp->v));
}
void	normal_expand(t_list *tmp, t_env **env)
{
	int		i;
	int		j;
	char	*p;
	char	*x;

	i = 0;
	j = 0;
	while (tmp->command[i] && tmp->command[i] != '$')
		i++;
	p = ft_substr(tmp->command, j, i - j);
	while (tmp->command[i])
	{
		i++;
		p = ft_strjoin(p, special_expand(tmp->command, &i));
		j = i;
		while (tmp->command[i] && tmp->command[i] != '$')
			i++;
		x = check_env(ft_substr(tmp->command, j, i - j),env);
		if (x)
			p = ft_strjoin(p, x);
		j = i;
		while (tmp->command[i] && tmp->command[i] != '$')
			i++;
		x = ft_substr(tmp->command, j, i - j);
		p = ft_strjoin(p, x);
		if (tmp->command[i] == '$' && tmp->command[i + 1] == '\0')
		{
			p = ft_strjoin(p, ft_strdup("$"));
			i++;
		}
	}
	free(tmp->command);
	tmp->command = ft_strjoin(ft_strdup(""), p);
}
char	*normal_expand_helper1(char *s, t_env **env)
{
	int		i;
	int		j;
	char	*p;
	char	*x;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '$')
		i++;
	p = ft_substr(s, j, i - j);
	while (s[i])
	{
		i++;
		p = ft_strjoin(p, special_expand(s, &i));
		j = i;
		while (s[i] && s[i] != '$')
			i++;
		x = check_env(ft_substr(s, j, i - j),env);
		if (x)
			p = ft_strjoin(p, x);
		j = i;
		while (s[i] && s[i] != '$')
			i++;
		x = ft_substr(s, j, i - j);
		p = ft_strjoin(p, x);
		if (s[i] == '$' && s[i + 1] == '\0')
		{
			p = ft_strjoin(p, ft_strdup("$"));
			i++;
		}
	}
	free(s);
	return (p);
}

char	*normal_expand_helper2(char *s, t_env **env)
{
	int		i;
	int		j;
	char	*p;
	char	*x;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '$')
		i++;
	p = ft_substr(s, j, i - j);
	while (s[i])
	{
		i++;
		p = ft_strjoin(p, special_expand(s, &i));
		j = i;
		while (s[i] && s[i] != '$')
		{
			if (s[i] == '\'' || s[i] == ' ')
				break ;
			i++;
		}
		x = check_env_q(ft_substr(s, j, i - j),env);
		if (x)
			p = ft_strjoin(p, x);
		j = i;
		while (s[i] && s[i] != '$')
			i++;
		x = ft_substr(s, j, i - j);
		p = ft_strjoin(p, x);
		if (s[i] == '$' && s[i + 1] == '\0')
		{
			p = ft_strjoin(p, ft_strdup("$"));
			i++;
		}
	}
	free(s);
	return (p);
}
