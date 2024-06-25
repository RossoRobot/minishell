/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:45:21 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/25 15:05:03 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	first_child_process(t_shell *shell, t_list *list, int *pipes,
		int temp_fd)
{
	int	ret;

	ret = 0;
	if ((dup2(temp_fd, STDIN_FILENO) == -1) || dup2(pipes[1], STDOUT_FILENO) ==
		-1)
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
	int		 i;
	pid_t	pid;
    int     fd[2];
	t_list	**list;

	i = 0;
	list = shell->lists;
	while (i < shell->n_pipes + 1)
	{
		if (pipe(fd) == -1)
			free_exit(shell, 0);
		pid = fork();
		if (pid < 0)
			exit (EXIT_FAILURE);
		if (pid == 0)
			pick_child_process(shell, i, fd, temp_fd);
        else
			close_fds(shell, fd, temp_fd);
		i++;
	}
    wait_for_child(shell);
	return (0);
}

void	pick_child_process(t_shell *shell, int i, int *pipes, int temp_fd)
{
	t_list	**list;
	
	list = shell->lists;
	if (i < shell->n_pipes)
		first_child_process(shell, list[i], pipes, temp_fd);
	else
		last_child_process(shell, list[i], pipes, temp_fd);
	exit(EXIT_SUCCESS);
}

void	close_fds(t_shell *shell, int *fd, int temp_fd)
{
	close(fd[1]);
	close(temp_fd);
	temp_fd = dup(fd[0]);
	if (temp_fd == -1)
	{
		close(fd[0]);
		free_parse(shell);
		free_exit(shell, 1);
	}
	close(fd[0]);
}

void	wait_for_child(t_shell *shell)
{
	int	status;
	int	childexitstatus;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
		{
			childexitstatus = WEXITSTATUS(status);
			set_return_value(shell, childexitstatus);
		}
		else
			set_return_value(shell, 0);
	}
	return ;
}

