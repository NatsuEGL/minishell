/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 08:15:30 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/22 11:35:51 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dst, char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

int	ft_strcmp1(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	print_nodes2(t_list *s)
{
	t_list	*current;

	current = s;
	while (current != NULL)
	{
		ft_printf("[%s]---------[%c]\n", current ->command, current->type);
		current = current->next;
	}
}

void	print_nodes(t_env *s, int data)
{
	t_env	*current;

	current = s;
	while (current != NULL)
	{
		if (current && !current->v)
		{
			if (current && current->next)
				current = current->next;
			return ;
		}
		ft_putstr_fd(current->c, data);
		write(data, "=", 1);
		ft_putstr_fd(current->v, data);
		write(data, "\n", 1);
		current = current->next;
	}
}

void	print_node_export(t_env *s, int data)
{
	t_env	*current;

	current = s;
	while (current != NULL)
	{
		if (current->flag2 == 1 && current->v == NULL)
		{
			write(data, "declare -x ", 11);
			ft_putstr_fd(current->c, data);
			write(data, "\n", 1);
		}
		else
		{
			write(data, "declare -x ", 11);
			ft_putstr_fd(current->c, data);
			write(data, "=", 1);
			write(data, "\"", 1);
			ft_putstr_fd(current->v, data);
			write(data, "\"", 1);
			write(data, "\n", 1);
		}
		current = current->next;
	}
}
