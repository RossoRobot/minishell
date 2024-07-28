/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:45:21 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/28 17:26:53 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

static void	builtin_option(t_shell *shell, t_list *temp, char **arr)
{
	free_arr(arr);
	execute_builtin(shell, temp);
	reset_fds(shell, shell->stdin_backup, shell->stdout_backup);
}

int	execute_it(t_shell *shell, char **arr, t_list *list)
{
	char	*path;
	t_list	*temp;

	temp = find_command(list);
	if (!temp)
	{
		free_arr(arr);
		return (close_all_fds(), 0);
	}
	if (temp->type >= 10 && temp->type <= 16)
		return (builtin_option(shell, temp, arr), 0);
	path = get_path(shell, temp);
	shell->env_arr = transform_list_to_arr(shell, shell->env_line);
	if (!(shell->env_arr))
		free_exit(shell, 1);
	if (execve(path, arr, shell->env_arr) == -1)
	{
		print_error_msg(errno, path);
		free(path);
		free_arr(arr);
		free_exit(shell, 1);
	}
	return (0);
}

static void	write_access_err(char *str, int flag)
{
	if (flag == 1)
	{
		if (access(str, F_OK) == 0 && access(str, W_OK) == -1)
		{
			ft_putstr_fd("permission denied: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	else
	{
		if (access(str, F_OK) == -1)
		{
			ft_putstr_fd("No such file or directory: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("\n", 2);
			return ;
		}
		if (access(str, R_OK) == -1)
		{
			ft_putstr_fd("permission denied: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("\n", 2);
		}
	}
}

int	redirect_input(t_shell *shell, t_list *list, char **arr, t_list *list_begin)
{
	int		fd;
	t_list	*cmd;
	t_shell	*dumm;
	char	**dummy;

	dummy = arr;
	dumm = shell;
	cmd = find_command(list_begin);
	write_access_err(list->next->content, 2);
	fd = open(list->next->content, O_RDONLY);
	if (fd == -1)
	{
		reset_fds(shell, shell->stdin_backup, shell->stdout_backup);
		set_return_value(shell, 1);
		return (-1);
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
		return (set_return_value(shell, 1), -1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		set_return_value(shell, 1);
		free_arr(arr);
		close(fd);
		free_exit(shell, 1);
	}
	return (close(fd), 0);
}
