/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:45:21 by mvolgger          #+#    #+#             */
/*   Updated: 2024/05/20 16:32:23 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	first_child_process(t_shell *shell, t_list *list, int *pipes, int temp_fd)
{
    dup2(temp_fd, STDIN_FILENO);
    dup2(pipes[1], STDOUT_FILENO);
    write(1, "hehe", 4);
	close(pipes[0]);
	close(pipes[1]);
    close(temp_fd);
	execute_command(shell, list);
	exit (EXIT_SUCCESS);
}

void	last_child_process(t_shell *shell, t_list *list, int *pipes, int temp_fd)
{
	char buf[3];
    
    dup2(temp_fd, STDIN_FILENO);
    //dup2(pipes[1], STDOUT_FILENO);
	close(pipes[0]);
	close(pipes[1]);
    close(temp_fd);
    read(STDIN_FILENO, buf, 3);
    write(1, buf, 3);
	execute_command(shell, list);
	exit (EXIT_SUCCESS);
    // close(pipes[1]);
	// dup2(pipes[0], STDIN_FILENO);
	// close(pipes[0]);
	// execute_command(shell, list);
	// exit(EXIT_SUCCESS);
}


int	forkex(t_shell *shell)
{
	int	    i;
	pid_t	pid;
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
		if (pid < 0)
		{
			perror("fork");
			exit (EXIT_FAILURE);
		}
		if (pid == 0)
		{
            if (i < shell->n_pipes)
                first_child_process(shell, list[i], fd, temp_fd);
            else
                last_child_process(shell, list[i], fd, temp_fd);
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
	
    int status;
    while (wait(&status) > 0)
    {
        
    }
	return (0);
}
