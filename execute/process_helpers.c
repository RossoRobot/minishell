/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:14:44 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/26 15:41:16 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

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

void	wait_for_child(t_shell *shell, int flag, int pid)
{
	int	status;
	int	childexitstatus;

	(void)flag;
	// if (flag == 1)
	// {
		if (g_var == 3)
			kill(pid, SIGQUIT);
		while (waitpid(pid, &status, WNOHANG) == 0)
		{
			//printf("g_var = %d \n", g_var);
			//sleep(1);
			if (g_var == 3)
			{
				kill(pid, SIGINT);
				set_return_value(shell, 131);
				//g_var = 0;
			}
		}
		//printf("g_var = %d \n", g_var);
		if (WIFEXITED(status))
		{
			childexitstatus = WEXITSTATUS(status);
			set_return_value(shell, childexitstatus);

		}
		else if (g_var != 3)
			set_return_value(shell, 0);
		else
			g_var = 0;
		return ;
	//}
	// wait(&status);
	// if (WIFEXITED(status))
	// {
	// 	childexitstatus = WEXITSTATUS(status);
	// 	set_return_value(shell, childexitstatus);
	// }
	// else
	// 	set_return_value(shell, 0);
}

void	no_pipe_child(t_shell *shell, t_list *list)
{
	if (is_redirection(shell, list) != 0)
	{
		prep_redir_exec(shell, list, 1);
		return ;
	}
	execute_binary(shell, list);
	exit(0);
}
