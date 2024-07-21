/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:47:18 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/21 19:23:34 by mvolgger         ###   ########.fr       */
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
	shell->pid[0] = fork();
	if (shell->pid[0] < 0)
		free_exit(shell, 1);
	if (shell->pid[0] == 0)
	{
		recieve_signal(shell, 3, 0, "0");
		no_pipe_child(shell, list);
	}
	else
	{
		wait_for_child(shell, 0, shell->pid, 1);
		free(shell->pid);
	}
}

int	execute_no_pipe(t_shell *shell, t_list *list)
{
	if (check_for_empty_cmd(shell, list, 0))
		return (127);
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
	int		count;

	temp = list;
	count = 0;
	while (temp->next)
	{
		count++;
		temp = temp->next;
	}
	if (check_for_redirections(temp))
	{
		if (flag == 1)
		{
			if (!ft_strncmp(temp->content, "", 1))
				return (ft_putstr_fd("Command \'\' not found\n", 2), 1);
			check_error(temp, count);
		}
		else
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
				2);
		return (1);
	}
	return (0);
}

void	check_error(t_list *temp, int count)
{
	if (count)
	{
		ft_putstr_fd("minishell: syntax error", 2);
		ft_putstr_fd(" near unexpected token `newline'\n", 2);
	}
	else
	{
		ft_putstr_fd(temp->content, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}
