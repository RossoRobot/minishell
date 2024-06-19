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

int	g_var;

void	handler(int sig)
{
	int	dummy;

	dummy = sig;
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

void	heredoc_helper(t_shell *shell, char *content, t_list *ptr, char *tmp)
{
	recieve_signal(shell, 1);
	free(content);
	handle_node(ptr, tmp);
}

int	write_free(int fd, char **cmd)
{
	write(fd, *cmd, ft_strlen(*cmd));
	free(*cmd);
	return (1);
}

void	negative_fd(t_shell *shell, int fd)
{
	if (fd == -1)
		free_exit(shell, 1);
}
