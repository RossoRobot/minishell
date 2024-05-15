/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:28:17 by mvolgger          #+#    #+#             */
/*   Updated: 2024/05/15 10:04:57 by mvolgger         ###   ########.fr       */
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

char	**transform_list(t_shell *shell, t_list *list)
{
	t_list	*temp;
	char	**arr;
	int		i;
	int		j;

	temp = list;
	i = 0;
	j = 0;
	while (temp)
	{
		temp = temp->next;
		i++;	
	}
	temp = list;
	arr = (char **)malloc(sizeof(char *) * (i + 1));
	if (!arr)
		free_exit(shell, 0);
	arr[i] = NULL;
	while (j < i)
	{
		arr[j] = ft_strdup(shell, temp->content);
		temp = temp->next;
		j++;	
	}
	return (arr);
}

char	**trans_argv(t_shell *shell, t_list *list)
{
	int		i;
	int		j;
	char	**args;
	t_list	*temp;

	i = 0;
	j = 0;
	temp = list;
	while (temp)
	{
		temp = temp->next;
		i++;	
	}
	args = (char **)malloc(sizeof(char *) * (i + 1));
	if (!args)
		free_exit(shell, 0);
	args[i] = NULL;
	temp = list;
	while (j < i)
	{
		args[j] = ft_strdup(shell, temp->content);
		temp = temp->next;
		j++;
	}
	return (args);
}

int	execute_binary(t_shell *shell, t_list *list)
{
	char	**exec_arr;
	char	**argv;
	char	*path;
	
	exec_arr = transform_list(shell, list);
	if (!exec_arr)
		free_exit(shell, 0);
	path = get_path(shell, list);
	argv = trans_argv(shell, list);
	execve(path, argv, exec_arr);
	
	return (0);
}

int	execute_no_pipe(t_shell *shell, t_list *list)
{
	if (list->type >= 10 && list->type <= 16)
		execute_builtin(shell, list);
	else
		execute_binary(shell, list);
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