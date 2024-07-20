/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:45:21 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/20 21:17:46 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	first_child_process(t_shell *shell, t_list *list, int *pipes,
		int temp_fd)
{
	int	ret;

	ret = 0;
	if ((dup2(temp_fd, STDIN_FILENO) == -1)
		|| dup2(pipes[1], STDOUT_FILENO) == -1 || check_last_node(list, 1))
	{
		close(pipes[0]);
		close(pipes[1]);
		close(temp_fd);
		free_exit(shell, 1);
	}
	close(pipes[0]);
	close(pipes[1]);
	close(temp_fd);
	if (is_redirection(shell, list) != 0)
		prep_redir_exec(shell, list, 1);
	ret = execute_command(shell, list);
	free_exit(shell, 0);
	exit(ret);
}

void	last_child_process(t_shell *shell, t_list *list, int *pipes,
		int temp_fd)
{
	int	ret;

	ret = 0;
	if (dup2(temp_fd, STDIN_FILENO) == -1 || check_last_node(list, 2))
	{
		close(pipes[0]);
		close(pipes[1]);
		close(temp_fd);
		free_exit(shell, 1);
	}
	close(pipes[0]);
	close(pipes[1]);
	close(temp_fd);
	if (is_redirection(shell, list) != 0)
		prep_redir_exec(shell, list, 1);
	ret = execute_command(shell, list);
	free_exit(shell, ret);
}

int	forkex(t_shell *shell, int temp_fd)
{
	int		i;
	pid_t	*pid;
	int		fd[2];
	t_list	**list;

	i = 0;
	list = shell->lists;
	pid = malloc(sizeof(pid_t) * (shell->n_pipes + 1));
	if (!pid)
		free_exit(shell, 1);
	while (i < shell->n_pipes + 1)
	{
		if (pipe(fd) == -1)
			free_exit(shell, 0);
		pid[i] = fork();
		if (pid[i] < 0)
			free_exit(shell, 1);
		if (pid[i] == 0)
		{
			recieve_signal(shell, 3, 1, "0");
			pick_child_process(shell, i, fd, temp_fd);
		}
		else
			close_fds(shell, fd, temp_fd);
		i++;
	}
	wait_for_child(shell, 1, pid, i);
	return (close(temp_fd), 0);
}

int	cmd_position(t_list *list)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = find_command(list);
	while (temp != NULL && temp->type != 4 && temp->type != 5
		&& temp->type != 7)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
