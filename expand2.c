/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 08:42:09 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/21 10:07:45 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	separ_expand(t_list *tmp, t_env **env)
{
	int		i;
	int		j;
	t_var1	*var;

	var = malloc(sizeof(t_var1));
	i = 0;
	j = 0;
	var->p = malloc(1);
	var->p[0] = '\0';
	while (tmp->command[i])
	{
		j = i;
		while (tmp->command[i] && \
			(tmp->command[i] != '\"' && tmp->command[i] != '\''))
			i++;
		var->x = ft_substr(tmp->command, j, i - j);
		var->x = normal_expand_helper1(var->x, env);
		var->p = ft_strjoin(var->p, var->x);
		separ_expand_norm(&tmp, env, var, &i);
	}
	free(tmp->command);
	tmp->command = ft_strjoin(ft_strdup(""), var->p);
	free(var);
}

int	find_index(char *p, int i)
{
	if (p[i] == '\"')
	{
		i++;
		while (p[i] && p[i] != '\"')
			i++;
	}
	if (p[i] == '\'')
	{
		i++;
		while (p[i] && p[i] != '\'')
			i++;
	}
	return (i);
}

char	*special_expand(char *p, int *in)
{
	int		i;
	int		j;

	i = 0;
	p = p + *in;
	if (p[i] == '$')
	{
		p = ft_strdup("$");
		i++;
	}
	else if (p[i] == '0')
		p = special_expand_norm(p, &i);
	else if (p[i] >= '1' && p[i] <= '9')
	{
		j = i;
		while (p[i] >= '0' && p[i] <= '9')
			i++;
		p = ft_substr(p, j + 1, i - j);
	}
	else 
		p = ft_strdup("");
	(*in) = (*in) + i;
	return (p);
}
