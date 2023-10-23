/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 08:42:16 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/23 12:52:39 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_lst(t_list **list)
{
	t_list	*tmp;
	t_list	*tmp1;

	if (*list)
	{
		tmp = (*list);
		while (tmp != NULL)
		{
			tmp1 = tmp->next;
			free(tmp->command);
			free(tmp);
			tmp = tmp1;
		}
		*list = NULL;
	}
}

void	parsing(t_list **list, t_env **envp, char **envc)
{
	char	*cmd;

	(*envp) = fill_list(envc);
	(*envp)->es = 0;
	while (1)
	{
		cmd = readline("$ ");
		if (!cmd)
		{
			ft_putstr_fd("exit", 1);
			exit(0);
		}
		add_history(cmd);
		tokenizer(list, cmd, envp);
		execution_part(list, envp);
		ft_free_lst(list);
		free(cmd);
	}
}

void	tokenizer(t_list **list, char *p, t_env **envp)
{
	int		i;

	i = 0;
	while (p[i])
	{
		if (p[i] == ' ' || p[i] == '\t')
			i++;
		else if (p[i] == '|' || p[i] == '>' || p[i] == '<')
			i = is_separ(list, p, i);
		else
		{
			i = error_case(list, envp, i, p);
			if (i == -1)
				return ;
		}
	}
	tokinizer_norm(list, envp);
}

int	error_case(t_list **list, t_env **envp, int i, char *p)
{
	if (p[i] == '\"' || p[i] == '\'')
	{
		i = is_quote(list, p, i);
		if (i == -1)
		{
			ft_putstr_fd("syntax error near unexpected token\n", 2);
			(*envp)->es = 258;
			ft_free_lst(list);
			return (-1);
		}
	}
	else
	{
		i = is_char(list, p, i);
		if (i == -1)
		{
			ft_putstr_fd("syntax error near unexpected token\n", 2);
			(*envp)->es = 258;
			ft_free_lst(list);
			return (-1);
		}
	}
	return (i);
}

void	tokinizer_norm(t_list **list, t_env **envp)
{
	t_list	*tmp;

	tmp = (*list);
	specifie_type(list);
	if (syntax_error(list) == -1)
	{
		ft_putstr_fd("syntax error near unexpected token\n", 2);
		(*envp)->es = 258;
		ft_free_lst(list);
		return ;
	}
	(*envp)->flag = 0;
	if (check_if_separ(list, "<<") == -1)
		expand(list, envp);
	
}
