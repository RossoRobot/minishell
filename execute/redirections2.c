/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:45:21 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/06 17:07:38 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	reset_fds(t_shell *shell, int stdin_backup, int stdout_backup)
{
	if (dup2(stdin_backup, STDIN_FILENO) == -1)
	{
		free_exit(shell, 1);
	}
	close(stdin_backup);
	if (dup2(stdout_backup, STDOUT_FILENO) == -1)
	{
		close(stdin_backup);
		free_exit(shell, 1);
	}
	close(stdout_backup);
}

t_list	*find_command(t_list *list)
{
	t_list	*temp;
	t_list	*temp2;

	temp = list;
	while (temp != NULL)
	{
		if ((temp->type >= 10 && temp->type <= 16) || temp->type == 0
			|| temp->type == 2)
		{
			temp2 = temp;
			while (temp2 != NULL)
			{
				set_type(temp2);
				temp2 = temp2->next;
			}
			return (temp);
		}
		if ((temp->type >= 4 && temp->type <= 7))
		{
			temp = temp->next;
		}
		temp = temp->next;
	}
	return (temp);
}

int	execute_it(t_shell *shell, char **arr, t_list *list)
{
	char	*path;
	t_list	*temp;

	temp = find_command(list);
	if (temp->type >= 10 && temp->type <= 16)
	{
		free_arr(arr);
		execute_builtin(shell, temp);
		reset_fds(shell, shell->stdin_backup, shell->stdout_backup);
		return (0);
	}
	path = get_path(shell, temp);
	shell->env_arr = transform_list_to_arr(shell, shell->env_line);
	if (!(shell->env_arr))
		free_exit(shell, 1);
	if (execve(path, arr, shell->env_arr) == -1)
	{
		ft_putstr_fd(temp->content, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(path);
		free_arr(arr);
		free_exit(shell, 1);
	}
	return (0);
}

int	redirect_input(t_shell *shell, t_list *list, char **arr)
{
	int	fd;

	fd = open(list->content, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("HERE:no such file or directory: ", 2);
		ft_putstr_fd(list->content, 2);
		ft_putstr_fd("\n", 2);
		free_arr(arr);
		free_exit(shell, 1);
	}
	dup2(fd, STDIN_FILENO);
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
	if (append == 0)
		fd = open(list->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (append == 1)
		fd = open(list->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(list->content, 2);
		ft_putstr_fd(": permission denied\n", 2);
		return (free_arr(arr), -1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		free_arr(arr);
		close(fd);
		free_exit(shell, 1);
	}
	return (close(fd), 0);
}
