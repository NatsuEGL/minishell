/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 21:18:19 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/20 16:26:42 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_node(t_env *head, char *command)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		if (!ft_strcmp(current->c, command))
			return (current);
		current = current->next;
	}
	return (0);
}

char	*command_ret(char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	s = malloc(i + 1);
	if (!s)
		return (0);
	j = 0;
	while (str[j] && j < i)
	{
		s[j] = str[j];
		j++;
	}
	s[i] = '\0';
	return (s);
}

char	*value_ret(char *str)
{
	char	*s;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (0);
	i++;
	s = ft_substr(str, i, ft_strlen(str) - i);
	return (s);
}

int	cheking_only(char *c)
{
	int	is_valid_command;
	int	i;

	i = 0;
	is_valid_command = 1;
	while (c[i])
	{
		if (ft_isalnum(c[i] == 0))
		{
			is_valid_command = 0;
			return (0);
		}
		i++;
	}
	return (1);
}

void	update_or_add_env(t_env **envp, char **p)
{
	t_env	*existing;
	t_env	*new_env;
	t_var3	*vars;

	vars = malloc(sizeof(t_var3));
	p++;
	new_env = NULL;
	while (*p)
	{
		if (only_alnum(*p) == 1)
		{
			export_initialisation(p, &vars, envp, &existing);
			if (cheking_only(*p) == 1)
			{
				if (existing)
					existing_norm(p, &vars, &existing);
				else
					not_exesting_norm(new_env, &vars, p, envp);
			}
		}
		else
			return ;
		p++;
	}
}
