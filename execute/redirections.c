/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:42:50 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/27 17:26:19 by mvolgger         ###   ########.fr       */
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

int	cmd_position(t_list *list)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = find_command(list);
	while (temp != NULL && temp->type != 4 && temp->type != 5
		&& temp->type != 7)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	prep_redir_exec(t_shell *shell, t_list *list, int flag)
{
	t_list	*temp;
	char	**cmd_arr;
	int		i;
	int		j;

	j = 0;
	i = cmd_position(list);
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
		free_exit(shell, 1);
	}
}

void	dup_stds(t_shell *shell)
{
	shell->stdin_backup = dup(STDIN_FILENO);
	if (shell->stdin_backup == -1)
	{
		free_exit(shell, 1);
	}
	shell->stdout_backup = dup(STDOUT_FILENO);
	if (shell->stdout_backup == -1)
	{
		close(shell->stdin_backup);
		free_exit(shell, 1);
	}
}

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
		{
			execute_it(shell, arr, list);
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
