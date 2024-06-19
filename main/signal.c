/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:56:09 by kbrauer           #+#    #+#             */
/*   Updated: 2024/06/19 11:56:10 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	handler(int sig)
{
	g_var = 2;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

//VS code denkt etwas passt da nicht (rot), ist aber alles ok
void	recieve_signal(t_shell *shell, int flag)
{
	if (flag == 0)
	{
		if (signal(SIGINT, &handler) == SIG_ERR)
			ft_exit(shell, NULL);
	}
	else
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR)
			ft_exit(shell, NULL);
	}
}
