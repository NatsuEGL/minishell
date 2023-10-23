/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:09:12 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/17 12:07:24 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	normal_expand(t_list *tmp, t_env **env)
{
	int		i;
	int		j;
	t_var1	*var;

	var = malloc(sizeof(t_var1));
	i = 0;
	j = 0;
	while (tmp->command[i] && tmp->command[i] != '$')
		i++;
	var->p = ft_substr(tmp->command, j, i - j);
	while (tmp->command[i])
	{
		i++;
		var->p = ft_strjoin(var->p, special_expand(tmp->command, &i));
		normal_expand_helper2_norm(tmp->command, var, env, &i);
	}
	free(tmp->command);
	tmp->command = ft_strjoin(ft_strdup(""), var->p);
}

char	*normal_expand_helper1(char *s, t_env **env)
{
	int		i;
	int		j;
	t_var1	*var;

	var = malloc(sizeof(t_var1));
	i = 0;
	j = 0;
	while (s[i] && s[i] != '$')
		i++;
	var->p = ft_substr(s, j, i - j);
	while (s[i])
	{
		i++;
		var->p = ft_strjoin(var->p, special_expand(s, &i));
		j = i;
		while (s[i] && s[i] != '$')
			i++;
		var->x = check_env(ft_substr(s, j, i - j), env);
		if (var->x)
			var->p = ft_strjoin(var->p, var->x);
		j = i;
		normal_expand_helper1_norm(s, &i, var);
	}
	free(s);
	return (var->p);
}

char	*normal_expand_helper2(char *s, t_env **env)
{
	int		i;
	int		j;
	t_var1	*var;

	var = malloc(sizeof(t_var1));
	i = 0;
	j = 0;
	while (s[i] && s[i] != '$')
		i++;
	var->p = ft_substr(s, j, i - j);
	while (s[i])
	{
		i++;
		var->p = ft_strjoin(var->p, special_expand(s, &i));
		j = i;
		normal_expand_helper2_norm(s, var, env, &i);
	}
	free(s);
	return (var->p);
}
