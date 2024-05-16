/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:28:17 by mvolgger          #+#    #+#             */
/*   Updated: 2024/05/16 15:13:17 by mvolgger         ###   ########.fr       */
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
	else
		execute_binary(shell, list);
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
	char	**argv;
	char	*path;
	int i = 0;
	
	shell->env_arr = transform_list_to_arr(shell, shell->env_line);
	if (!(shell->env_arr))
		free_exit(shell, 0);
	path = get_path(shell, list);
	argv = trans_argv(shell, list);
	if (execve(path, argv, shell->env_arr) == -1)
	{
		free(path);
		free_arr(argv);
		free_arr(shell->env_arr);
	}
	return (0);
}

void	execute_onechild(t_shell *shell, t_list *list, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execute_binary(shell, list);
	exit (0);
}

int	execute_no_pipe(t_shell *shell, t_list *list)
{
	int		fd[2];
	pid_t	pid;
	char	buffer[BUFSIZ];
	ssize_t	bytes_read;

	if (list->type >= 10 && list->type <= 16)
		execute_builtin(shell, list);
	else
	{
		if (pipe(fd) == -1)
			free_exit(shell, 1);
		pid = fork();
		if (pid < 0)
			free_exit(shell, 1);
		if (pid == 0)
			execute_onechild(shell, list, fd);
		else
		{
			close(fd[1]);
			while ((bytes_read = read(fd[0], buffer, sizeof(buffer))) > 0)
            	write(STDOUT_FILENO, buffer, bytes_read);
			close(fd[0]);
			wait(NULL);
		}
	}
	return (0);
}

int	forkex(t_shell *shell, int (*pipes)[2])
{
	int	i;
	pid_t	pid;
	t_list	*list;

	i = 0;
	list = shell->lists[0];
	while (i < shell->n_pipes + 1)
	{
		pid = fork();
		if (pid == -1)
			free_exit(shell, 0);
		if (pid == 0)
		{
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < shell->n_pipes)
				dup2(pipes[i][1], STDOUT_FILENO);
			child_process(shell, list, pipes[i]);
		}
		i++;
		list = list->next;
	}
	return (0);
}

int	execute(t_shell *shell)
{
	int		(*pipes)[2];
	int		i;

	i = 0;
	if (shell->lists[1] == NULL)
		return (execute_no_pipe(shell, shell->lists[0]));
	pipes = malloc(sizeof(int[shell->n_pipes][2]));
	if (pipes == NULL)
		free_exit(shell, 1);
	while (i < shell->n_pipes)
	{
		if (pipe(pipes[i]) == -1)
			free_exit(shell, 0);
		i++;
	}
	forkex(shell, pipes);
	return (0);
}

