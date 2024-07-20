/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:47:18 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/20 21:20:42 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

static int	check_for_builtin(t_shell *shell, t_list *list)
{
	t_list	*temp;
	void	*dummy;

	dummy = shell;
	temp = list;
	if (!(temp->type >= 4 && temp->type <= 7))
		return (0);
	while (temp)
	{
		if (temp->type >= 4 && temp->type <= 7)
			temp = temp->next;
		if (temp)
			temp = temp->next;
		if (temp)
		{
			if (temp->type >= 10 && temp->type <= 16)
				return (1);
		}
	}
	return (0);
}

static void	fork_no_pipe(t_shell *shell, t_list *list)
{
	shell->pid = malloc(4);
	if (!shell->pid)
		free_exit(shell, 1);
	if (pipe(shell->fd) == -1)
		free_exit(shell, 1);
	shell->pid[0] = fork();
	if (shell->pid[0] < 0)
		free_exit(shell, 1);
	if (shell->pid[0] == 0)
	{
		close(shell->fd[0]);
		close(shell->fd[1]);
		recieve_signal(shell, 3, 0, "0");
		no_pipe_child(shell, list);
	}
	else
	{
		close(shell->fd[1]);
		close(shell->fd[0]);
		wait_for_child(shell, 0, shell->pid, 1);
	}
}

int	execute_no_pipe(t_shell *shell, t_list *list)
{
	if (check_last_node(list, 1))
		return (1);
	if (is_redirection(shell, list) != 0 && ((list->type >= 10
				&& list->type <= 16) || check_for_builtin(shell, list)))
		return (prep_redir_exec(shell, list, 0), 0);
	if (list->type >= 10 && list->type <= 16)
		execute_builtin(shell, list);
	else
		fork_no_pipe(shell, list);
	return (0);
}

int	check_last_node(t_list *list, int flag)
{
	t_list	*temp;

	temp = list;
	while (temp->next)
		temp = temp->next;
	if (!ft_strncmp(temp->content, "<", ft_strlen(temp->content))
		|| !ft_strncmp(temp->content, "<<", ft_strlen(temp->content))
		|| !ft_strncmp(temp->content, ">>", ft_strlen(temp->content))
		|| !ft_strncmp(temp->content, ">", ft_strlen(temp->content)))
	{
		if (flag == 1)
		{
			ft_putstr_fd("minishell: syntax error", 2);
			ft_putstr_fd(" near unexpected token `newline'\n", 2);
		}
		else
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
				2);
		return (1);
	}
	return (0);
}
