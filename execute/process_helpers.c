/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:14:44 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/21 17:03:17 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	pick_child_process(t_shell *shell, int i, int *pipes, int temp_fd)
{
	t_list	**list;

	list = shell->lists;
	if (check_for_empty_cmd(shell, list[i], 1))
		free_exit(shell, 127);
	if (i < shell->n_pipes)
		first_child_process(shell, list[i], pipes, temp_fd);
	else
		last_child_process(shell, list[i], pipes, temp_fd);
	close_all_fds();
	close(shell->stdin_backup);
	close(shell->stdout_backup);
	free_parse(shell);
	free(shell);
	exit(EXIT_SUCCESS);
}

void	wait_for_child(t_shell *shell, int flag, int *pid, int x)
{
	int	status;
	int	i;

	i = 0;
	(void)flag;
	while (i < x)
	{
		if (waitpid(pid[i], &status, WNOHANG) == 0)
		{
			if (g_var == 3)
			{
				kill(pid[i], SIGINT);
				set_return_value(shell, 131);
			}
		}
		else
			i++;
	}
	wait_for_child2(shell, status);
}

void	wait_for_child2(t_shell *shell, int status)
{
	int	childexitstatus;

	if (WIFEXITED(status))
	{
		childexitstatus = WEXITSTATUS(status);
		set_return_value(shell, childexitstatus);
	}
	else if (WIFSIGNALED(status))
	{
		childexitstatus = WTERMSIG(status);
		if (g_var == 3)
			set_return_value(shell, 131);
		else
			set_return_value(shell, 128 + childexitstatus);
	}
	else
		set_return_value(shell, 0);
	g_var = 0;
}

static int	check_for_bad_things(t_shell *shell, t_list *list)
{
	t_list	*temp;
	void	*dummy;

	dummy = shell;
	temp = list;
	if (!ft_strncmp(temp->content, "<<", ft_strlen(temp->content))
		|| ft_strncmp(temp->content, "<", ft_strlen(temp->content))
		|| ft_strncmp(temp->content, ">", ft_strlen(temp->content))
		|| ft_strncmp(temp->content, ">>", ft_strlen(temp->content)))
	{
		if (!temp->next)
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			return (1);
		}
	}
	return (0);
}

void	no_pipe_child(t_shell *shell, t_list *list)
{
	if (is_redirection(shell, list) != 0)
	{
		if (check_for_bad_things(shell, list))
		{
			close(shell->fd[1]);
			free_exit(shell, 2);
		}
		prep_redir_exec(shell, list, 1);
	}
	execute_binary(shell, list);
	exit(0);
}
