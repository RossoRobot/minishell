/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:42:50 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/26 15:30:09 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	is_redirection(t_shell *shell, t_list *list)
{
	t_list	*temp;
	int		ret;
	t_shell	*dummy;

	dummy = shell;
	ret = 0;
	temp = list;
	while (temp)
	{
		if (temp->type == 4 || temp->type == 5 || temp->type == 7)
			ret++;
		temp = temp->next;
	}
	return (ret);
}

void	prep_redir_exec(t_shell *shell, t_list *list, int flag)
{
	t_list	*temp;
	char	**cmd_arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = find_command(list);
	while (temp != NULL && temp->type != 4 && temp->type != 5 && temp->type != 7)
	{
		i++;
		temp = temp->next;
	}
	cmd_arr = (char **)malloc(sizeof(char *) * (i + 1));
	if (!cmd_arr)
		free_exit(shell, 1);
	cmd_arr[i] = NULL;
	temp = find_command(list);
	while (j < i)
	{
		cmd_arr[j] = ft_strdup(shell, temp->content);
		temp = temp->next;
		j++;
	}
	temp = list;
	exec_redir(shell, temp, cmd_arr, list);
	if (flag == 1)
	{
		free_parse(shell);
		free_exit(shell, 1);
	}
}
int	exec_redir(t_shell *shell, t_list *temp, char **arr, t_list *list)
{
	int	stdin_backup;
	int	stdout_backup;
	int	ret;

	ret = 0;
	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup == -1)
		return (-1);
	stdout_backup = dup(STDOUT_FILENO);
	if (stdout_backup == -1)
	{
		close(stdin_backup);
		return (-1);
	}
	while (temp != NULL)
	{
		while (temp != NULL && temp->type != 4 && temp->type != 5
			&& temp->type != 7)
			temp = temp->next;
		if (temp == NULL)
		{
			execute_it(shell, arr, list, stdin_backup, stdout_backup);
			return (0);
		}
		else if (temp->type == 5)
			ret = redirect_output(shell, temp->next, arr, 0);
		else if (temp->type == 7)
			ret = redirect_output(shell, temp->next, arr, 1);
		else if (temp->type == 4)
			ret = redirect_input(shell, temp->next, arr);
		temp = temp->next;
		if (ret == -1)
			return (-1);
	}
	return (ret);
}

void	reset_fds(t_shell *shell, int stdin_backup, int stdout_backup)
{
	if (dup2(stdin_backup, STDIN_FILENO) == -1)
	{
		free_parse(shell);
		free_exit(shell, 1);
	}
	close(stdin_backup);
	if (dup2(stdout_backup, STDOUT_FILENO) == -1)
	{
		close(stdin_backup);
		free_parse(shell);
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

int	execute_it(t_shell *shell, char **arr, t_list *list, int stdin_backup,
		int stdout_backup)
{
	char	*path;
	t_list	*temp;

	temp = find_command(list);
	if (temp->type >= 10 && temp->type <= 16)
	{
		free_arr(arr);
		execute_builtin(shell, temp);
		reset_fds(shell, stdin_backup, stdout_backup);
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
		free_parse(shell);
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
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(list->content, 2);
		ft_putstr_fd("\n", 2);
		free_parse(shell);
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
		free_arr(arr);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		free_arr(arr);
		close(fd);
		free_parse(shell);
		free_exit(shell, 1);
	}
	close(fd);
	return (0);
}
