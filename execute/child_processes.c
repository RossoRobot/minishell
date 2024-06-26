/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:45:21 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/25 15:32:52 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	first_child_process(t_shell *shell, t_list *list, int *pipes,
		int temp_fd)
{
	int	ret;

	ret = 0;
	if ((dup2(temp_fd, STDIN_FILENO) == -1)
		|| dup2(pipes[1], STDOUT_FILENO) == -1)
	{
		close(pipes[0]);
		close(pipes[1]);
		close(temp_fd);
		free_parse(shell);
		free_exit(shell, 1);
	}
	close(pipes[0]);
	close(pipes[1]);
	close(temp_fd);
	if (is_redirection(shell, list) != 0)
		prep_redir_exec(shell, list, 1);
	ret = execute_command(shell, list);
	free_parse(shell);
	free_exit(shell, 0);
	exit(ret);
}

void	last_child_process(t_shell *shell, t_list *list, int *pipes,
		int temp_fd)
{
	int	ret;

	ret = 0;
	if (dup2(temp_fd, STDIN_FILENO) == -1)
	{
		close(pipes[0]);
		close(pipes[1]);
		close(temp_fd);
		free_parse(shell);
		free_exit(shell, 1);
	}
	close(pipes[0]);
	close(pipes[1]);
	close(temp_fd);
	if (is_redirection(shell, list) != 0)
		prep_redir_exec(shell, list, 1);
	ret = execute_command(shell, list);
	free_parse(shell);
	free_exit(shell, ret);
}

int	forkex(t_shell *shell, int temp_fd)
{
	int		i;
	pid_t	pid;
	int		fd[2];
	t_list	**list;

	i = 0;
	list = shell->lists;
	while (i < shell->n_pipes + 1)
	{
		if (pipe(fd) == -1)
			free_exit(shell, 0);
		//recieve_signal(shell, 1, 0);
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		if (pid == 0)
		{
			recieve_signal(shell, 3, 1);
			pick_child_process(shell, i, fd, temp_fd);
		}
		else
			close_fds(shell, fd, temp_fd);
		i++;
	}
	wait_for_child(shell, 1, pid);
	return (0);
}
