/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 08:42:16 by aamhal            #+#    #+#             */
/*   Updated: 2023/09/21 10:42:56 by akaabi           ###   ########.fr       */
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

void	parsing(t_list **list, t_env **envp)
{
	char	*cmd;

	while (1)
	{
		cmd = readline("$ ");
		if (!ft_strncmp(cmd, "exit", 4))
			return ;
		add_history(cmd);
		tokenizer(list, cmd, envp);
    	open_pipe(list, envp);
		builting(list,envp);
		free(cmd);
	}
}

void	tokenizer(t_list **list, char *p, t_env **envp)
{
	// t_list	*tmp;
	(void)envp;
	int		i;

	i = 0;
	while (p[i])
	{
		if (p[i] == ' ' || p[i] == '\t')
			i++;
		else if (p[i] == '|' || p[i] == '>' || p[i] == '<')
			i = is_separ(list, p, i);
		else if (p[i] == '\"' || p[i] == '\'')
			i = is_quote(list, p, i);
		else
			i = is_char(list, p, i);
	}
	specifie_type(list);
	if (syntax_error(list) == -1)
	{
		ft_putstr_fd("syntax error near unexpected token\n", 2);
		ft_free_lst(list);
		return ;
	}
	// expand(list,envp);
	// check_echo(list,1);
    // print_nodes2(*list);
	// execution()
	// ft_free_lst(list);
}
