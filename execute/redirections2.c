/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:45:21 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/29 20:17:11 by mvolgger         ###   ########.fr       */
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
	int		flag;

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
	check_for_dir(shell, list->content, path, arr);
	if (execve(path, arr, shell->env_arr) == -1)
	{
		flag = print_error_msg(errno, path);
		free(path);
		free_arr(arr);
		free_exit(shell, flag);
	}
	return (0);
}

void	write_access_err(char *str, int flag)
{
	if (flag == 1)
	{
		if (access(str, F_OK) == 0 && access(str, W_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
	}
	else
	{
		if (access(str, F_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return ;
		}
		if (access(str, R_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
	}
}
