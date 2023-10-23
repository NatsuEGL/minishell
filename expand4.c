/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:12:00 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/17 12:07:16 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	separ_expand_norm(t_list **list, t_env **env, t_var1 *var, int *i)
{
	int		j;
	t_list	*tmp;

	j = *i + 1;
	tmp = *list;
	if (tmp->command[*i] == '\"')
	{
		*i = find_index(tmp->command, *i);
		var->x = ft_substr(tmp->command, j, *i - j);
		var->x = normal_expand_helper2(var->x, env);
		i++;
		var->p = ft_strjoin(var->p, var->x);
	}
	else if (tmp->command[*i] == '\'')
	{
		*i = find_index(tmp->command, *i);
		var->x = ft_substr(tmp->command, j, *i - j);
		*i = *i + 1;
		var->p = ft_strjoin(var->p, var->x);
	}
}

char	*special_expand_norm(char *p, int *i)
{
	int		j;
	char	*x;

	j = *i;
	while (p[*i] >= '0' && p[*i] <= '9')
		*i = *i + 1;
	x = ft_substr(p, j + 1, *i - j);
	p = ft_strdup("");
	p = ft_strjoin(ft_strdup("minishell"), x);
	return (p);
}

void	normal_expand_helper1_norm(char *s, int *i, t_var1 *var)
{
	int	j;

	j = *i;
	while (s[*i] && s[*i] != '$')
		i++;
	var->x = ft_substr(s, j, *i - j);
	var->p = ft_strjoin(var->p, var->x);
	if (s[*i] == '$' && s[*i + 1] == '\0')
	{
		var->p = ft_strjoin(var->p, ft_strdup("$"));
		i++;
	}
}

void	normal_expand_helper2_norm(char *s, t_var1 *var, t_env **env, int *i)
{
	int	j;

	j = *i;
	while (s[*i] && s[*i] != '$')
	{
		if (s[*i] == '\'' || s[*i] == ' ')
			break ;
		*i = *i + 1;
	}
	var->x = check_env_q(ft_substr(s, j, *i - j), env);
	if (var->x)
		var->p = ft_strjoin(var->p, var->x);
	j = *i;
	while (s[*i] && s[*i] != '$')
		i++;
	var->x = ft_substr(s, j, *i - j);
	var->p = ft_strjoin(var->p, var->x);
	if (s[*i] == '$' && s[*i + 1] == '\0')
	{
		var->p = ft_strjoin(var->p, ft_strdup("$"));
		i++;
	}
}
