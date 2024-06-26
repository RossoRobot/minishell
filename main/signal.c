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
	g_var = sig;
	//dprintf(2, "value is: %d\n", sig);
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
	//dprintf(2, "value is: %d\n", sig);
	if (sig == 2)
	{
		write(1, "\n", 1);
		// ioctl(STDIN_FILENO, TIOCSTI, "\n");
		// rl_on_new_line();
		// rl_replace_line("", 0);
	}
	if (sig == 3)
	{
		dprintf(2, "Quit (core dumped)\n");
		//ioctl(STDIN_FILENO, TIOCSTI, "\n");
		//rl_on_new_line();
		//rl_replace_line("", 0);
	}
}

void lol(int num)
{
	(void)num;
	//exit(num + 128);
}

void	recieve_signal(t_shell *shell, int flag, int shellflag)
{
	shell->flag = shellflag;
	// dprintf(2, "hi\n");
	if (flag == 0) //for the parent
	{
		// if (!shellflag)
		// 	dprintf(2, "parent\n");
		if (signal(SIGINT, &handler) == SIG_ERR)
			ft_exit(shell, NULL);
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			ft_exit(shell, NULL);
	}
	else if (flag == 2)
	{
		//dprintf(2, "noninteractive\n");
		if (signal(SIGINT, &handler2) == SIG_ERR)
			ft_exit(shell, NULL);
		if (signal(SIGQUIT, &handler2) == SIG_ERR)
			ft_exit(shell, NULL);
		//if (shellflag == 1)
		//	set_return_value(shell, 130);
	}
	else if (flag == 3)
	{
		//dprintf(2, "child\n");
		if (signal(SIGINT, SIG_DFL) == SIG_ERR)
			ft_exit(shell, NULL);
		if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
			ft_exit(shell, NULL);
	}
}

void	heredoc_helper(t_shell *shell, char *content, t_list *ptr, char *tmp)
{
	recieve_signal(shell, 2, 0);
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
