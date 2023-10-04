/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 08:17:47 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/01 10:14:42 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void hundler(int signal)
{
	(void)signal;
	write(1,"\n",1);
	// rl_on_new_line();
	// rl_replace_line("",0);
	// rl_redisplay();
}

void ignore_signals()
{
	signal(SIGQUIT,SIG_IGN);
    signal(SIGINT,SIG_IGN);
}
void catch_signals()
{
	signal(SIGQUIT,SIG_IGN);
    signal(SIGINT,hundler);
}

void default_signals()
{
	signal(SIGQUIT,SIG_DFL);
    signal(SIGINT,SIG_DFL);
}