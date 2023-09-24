/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 22:00:20 by akaabi            #+#    #+#             */
/*   Updated: 2023/09/18 09:05:23 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back1(t_env **lst, t_env *new)
{
	t_env	*p;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		p = *lst;
		while (p->next)
			p = p -> next;
		p->next = new;
	}
	else
		*lst = new;
}