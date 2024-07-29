/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:52:28 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/29 20:55:56 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	exec_redir(t_shell *shell, t_list *temp, char **arr, t_list *list)
{
	int	ret;

	ret = 0;
	dup_stds(shell);
	while (temp != NULL)
	{
		while (temp != NULL && temp->type != 4 && temp->type != 5
			&& temp->type != 7)
			temp = temp->next;
		if (temp == NULL)
			return (execute_it(shell, arr, list));
		else if (temp->type == 5)
			ret = redirect_output(shell, temp->next, arr, 0);
		else if (temp->type == 7)
			ret = redirect_output(shell, temp->next, arr, 1);
		else if (temp->type == 4)
			ret = redirect_input(shell, temp, arr, list);
		if (ret == 1)
			return (free_arr(arr), ret);
		temp = temp->next;
		if (ret != 0)
			return (free_arr(arr), ret);
	}
	return (ret);
}

int	redirect_input(t_shell *shell, t_list *list, char **arr, t_list *list_begin)
{
	int		fd;
	t_list	*cmd;

	cmd = find_command(list_begin);
	write_access_err(list->next->content, 2);
	fd = open(list->next->content, O_RDONLY);
	if (fd == -1)
	{
		reset_fds(shell, shell->stdin_backup, shell->stdout_backup);
		set_return_value(shell, 1);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		set_return_value(shell, 1);
		free_arr(arr);
		close(fd);
		free_exit(shell, 1);
	}
	close(fd);
	return (0);
}

int	redirect_output(t_shell *shell, t_list *list, char **arr, int append)
{
	int		fd;
	void	*ptr;
	char	**ptr2;

	ptr = shell;
	ptr2 = arr;
	fd = 0;
	write_access_err(list->content, 1);
	if (append == 0)
		fd = open(list->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (append == 1)
		fd = open(list->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (set_return_value(shell, 1), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		set_return_value(shell, 1);
		free_arr(arr);
		close(fd);  
		free_exit(shell, 1);
	}
	return (close(fd), 0);
}

