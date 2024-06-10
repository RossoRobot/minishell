/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:45:21 by mvolgger          #+#    #+#             */
/*   Updated: 2024/05/27 12:16:35 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	first_child_process(t_shell *shell, t_list *list, int *pipes, int temp_fd)
{
	
    dup2(temp_fd, STDIN_FILENO);
    dup2(pipes[1], STDOUT_FILENO);
	close(pipes[0]);
	close(pipes[1]);
    close(temp_fd);
	if (is_redirection(shell, list) != 0)
		prep_redir_exec(shell, list);
	execute_command(shell, list);
	free_parse(shell);
	free_exit(shell, 0);
	exit (EXIT_SUCCESS);
}

void	last_child_process(t_shell *shell, t_list *list, int *pipes, int temp_fd)
{
    dup2(temp_fd, STDIN_FILENO);
	close(pipes[0]);
	close(pipes[1]);
    close(temp_fd);
	if (is_redirection(shell, list) != 0)
		prep_redir_exec(shell, list);
	execute_command(shell, list);
	free_parse(shell);
	free_exit(shell, 0);
	exit (EXIT_SUCCESS);
}


int	forkex(t_shell *shell)
{
	int	    i;
	pid_t	pid;
    int     status;
    int     fd[2];
    int     temp_fd;
	t_list	**list;

	i = 0;
	list = shell->lists;
    temp_fd = dup(STDIN_FILENO);
	while (i < shell->n_pipes + 1)
	{
		if (pipe(fd) == -1)
			free_exit(shell, 0);
		pid = fork();
		//store_pid(shell, pid);
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
        
    }
	return (0);
}
