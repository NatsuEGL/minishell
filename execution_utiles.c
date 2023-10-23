/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:38:14 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/20 17:46:41 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_separ(t_list **list, char *separ)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->command, separ) && tmp->type == 'S')
			return (0);
		tmp = tmp->next;
	}
	return (-1);
}
