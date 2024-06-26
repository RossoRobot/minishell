/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:45:52 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/25 15:53:46 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

static char	**trans_argv(t_shell *shell, t_list *list)
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

	check_some_things(shell, list);
	shell->env_arr = transform_list_to_arr(shell, shell->env_line);
	if (!(shell->env_arr))
		free_exit(shell, 0);
	path = get_path(shell, list);
	argv = trans_argv(shell, list);
	shell->sig_flag = true;
	recieve_signal(shell, 0, 1);
	if (execve(path, argv, shell->env_arr) == -1)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(path);
		free_arr(argv);
		free_parse(shell);
		free_exit(shell, 0);
		exit(127);
	}
	recieve_signal(shell, 2, 1);
	return (0);
}

int	execute_command(t_shell *shell, t_list *list)
{
	int	ret;

	ret = 0;
	if (list->type <= 16 && list->type >= 10)
	{
		ret = execute_builtin(shell, list);
		return (ret);
	}
	else
	{
		ret = execute_binary(shell, list);
		return (ret);
	}
}

int	execute_no_pipe(t_shell *shell, t_list *list)
{
	int		fd[2];
	pid_t	pid;

	if (is_redirection(shell, list) != 0 && (list->type >= 10
			&& list->type <= 16))
		return (prep_redir_exec(shell, list, 0), 0);
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
		{
			recieve_signal(shell, 3, 1);
			no_pipe_child(shell, list);
		}
		else
			wait_for_child(shell, 0, pid);
	}
	return (0);
}

int	execute(t_shell *shell)
{
	int	i;
	int	temp_fd;

	i = 0;
	if (shell->lists[1] == NULL)
		return (execute_no_pipe(shell, shell->lists[0]));
	temp_fd = dup(STDIN_FILENO);
	if (temp_fd == -1)
	{
		free_parse(shell);
		free_exit(shell, 1);
	}
	forkex(shell, temp_fd);
	return (0);
}
