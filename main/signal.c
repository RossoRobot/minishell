/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:56:09 by kbrauer           #+#    #+#             */
/*   Updated: 2024/06/27 11:56:19 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	g_var;

void	handler(int sig)
{
	g_var = sig;
	if (sig == 2)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	handler2(int sig)
{
	g_var = sig;
	if (sig == 2)
		write(1, "\n", 1);
	if (sig == 3)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	handler3(int sig)
{
	g_var = sig;
}

void	recieve_signal(t_shell *shell, int flag, int shellflag, char *str)
{
	shell->flag = shellflag;
	if (flag == 0)
	{
		if (signal(SIGINT, &handler) == SIG_ERR)
			ft_exit(shell, NULL);
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			ft_exit(shell, NULL);
	}
	else if (flag == 2)
	{
		if (signal(SIGINT, &handler2) == SIG_ERR)
			ft_exit(shell, NULL);
		if (signal(SIGQUIT, &handler2) == SIG_ERR)
			ft_exit(shell, NULL);
		if (shellflag == 1 && (check_shlvl(str) == 0))
			signal(SIGINT, &handler3);
	}
	else if (flag == 3)
	{
		if (signal(SIGINT, SIG_DFL) == SIG_ERR)
			ft_exit(shell, NULL);
		if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
			ft_exit(shell, NULL);
	}
}

void	heredoc_helper(t_shell *shell, char *content, t_list *ptr, char *tmp)
{
	recieve_signal(shell, 2, 0, "0");
	free(content);
	handle_node(shell, ptr, tmp);
}
