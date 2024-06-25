/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:45:21 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/25 12:17:44 by mvolgger         ###   ########.fr       */
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

// int	forkex(t_shell *shell)
// {
// 	int		i;
// 	pid_t	pid;
// 	int		fd[2];
// 	int		temp_fd;
// 	t_list	**list;

// 	i = 0;
// 	list = shell->lists;
// 	temp_fd = dup(STDIN_FILENO);
// 	while (i < shell->n_pipes + 1)
// 	{
// 		if (pipe(fd) == -1)
// 			free_exit(shell, 0);
// 		pid = fork();
// 		if (pid < 0)
// 		{
// 			perror("fork");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (pid == 0)
// 		{
// 			if (i < shell->n_pipes)
// 				first_child_process(shell, list[i], fd, temp_fd);
// 			else
// 				last_child_process(shell, list[i], fd, temp_fd);
// 			exit(EXIT_SUCCESS);
// 		}
// 		else
// 		{
// 			close(fd[1]);
// 			close(temp_fd);
// 			temp_fd = dup(fd[0]);
// 			close(fd[0]);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// void	wait_for_children(t_shell *shell)
// {
// 	int		status;
// 	int		child_exit_status;

// 	while (wait(&status) > 0)
// 	{
// 		if (WIFEXITED(status))
// 		{
// 			child_exit_status = WEXITSTATUS(status);
// 			set_return_value(shell, child_exit_status);
// 		}
// 		else
// 			set_return_value(shell, 0);
// 	}
// }

int	forkex(t_shell *shell)
{
	int	    i;
	pid_t	pid;
    int     status;
    int     fd[2];
    int     temp_fd;
	int 	child_exit_status;
	t_list	**list;

	i = 0;
	list = shell->lists;
    temp_fd = dup(STDIN_FILENO);
	while (i < shell->n_pipes + 1)
	{
		if (pipe(fd) == -1)
			free_exit(shell, 0);
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit (EXIT_FAILURE);
		}
		if (pid == 0)
		{
            if (i < shell->n_pipes)
			{
                first_child_process(shell, list[i], fd, temp_fd);
			}
            else
			{
                last_child_process(shell, list[i], fd, temp_fd);
				
			}
			exit(EXIT_SUCCESS);
		}
        else
        {
            close(fd[1]);
            close(temp_fd);
            temp_fd = dup(fd[0]);
            close(fd[0]);
        }
		i++;
	}
	i = 0;
	
    while (wait(&status) > 0)
    {
		if (WIFEXITED(status))
		{
			child_exit_status = WEXITSTATUS(status);
			set_return_value(shell, child_exit_status);
		}
		else
			set_return_value(shell, 0);
		
    }
	return (0);
}
