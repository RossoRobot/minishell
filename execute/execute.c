/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:28:17 by mvolgger          #+#    #+#             */
/*   Updated: 2024/04/23 19:33:44 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	execute_builtin(t_shell *shell, t_list *list)
{
	t_list *temp;

	temp = list;
	if (temp->type == export_a)
		execute_export(shell, temp);
	if (temp->type == env_a)
		execute_env(shell, temp);
	if (temp->type == unset_a)
		execute_unset(shell, temp);
	if (temp->type == cd_a)
		execute_cd(shell, temp);
	if (temp->type == pwd_a)
		pwd(shell);
	if (temp->type == exit_a)
		ft_exit(shell, list);
	return (0);
}

void	child_process(t_shell *shell, t_list *list, int *fd)
{
	if (list->type >= 10 && list->type <= 15)
		execute_builtin(shell, list);
	exit(0);
}

int	prepare_child_process(t_shell *shell, t_list *list)
{
	int	fd[2];
	int	status;

	pid_t	pid;
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		child_process(shell, list, fd);
	else
	{
		waitpid(pid, &status, 0);
	}
	return (0);
}

int	prepare_execution(t_shell *shell, t_list *list)
{
	transform_list_to_arr(shell, shell->env_line);
	prepare_child_process(shell, list);
	return (0);
}

int	execute_no_pipe(t_shell *shell, t_list *list)
{
	if (list->type >= 10 && list->type <= 16)
		execute_builtin(shell, list);
	return (0);
}

int	execute(t_shell *shell)
{
	t_list	**list;
	int		i;

	i = 0;
	list = shell->lists;
	if (list[1] == NULL)
		return(execute_no_pipe(shell, list[0]));
	while(list[i])
	{
		prepare_execution(shell, list[i]);
		i++;
	}
	
	return (0);
}