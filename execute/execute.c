/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:28:17 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/15 16:34:02 by mvolgger         ###   ########.fr       */
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
	if (temp->type == echo_a)
		execute_echo(shell, temp);
	return (0);
}

void	child_process(t_shell *shell, t_list *list)
{
	if (list->type >= 10 && list->type <= 15)
	{
		execute_builtin(shell, list);
	}
	else
		execute_binary(shell, list);
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
	
	shell->env_arr = transform_list_to_arr(shell, shell->env_line);
	if (!(shell->env_arr))
		free_exit(shell, 0);
	path = get_path(shell, list);
	argv = trans_argv(shell, list);
	if (execve(path, argv, shell->env_arr) == -1)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(path);
		free_arr(argv);
		free_parse(shell);
		free_exit(shell, 1);
	}
	return (0);
}
int	execute_command(t_shell *shell, t_list *list)
{
	if (list->type <= 16 && list->type >= 10)
	{
		execute_builtin(shell, list);
		return (0);
	}
	else
	{
		execute_binary(shell, list);
		return (0);
	}
}

int	execute_no_pipe(t_shell *shell, t_list *list)
{
	int		fd[2];
	pid_t	pid;

	if (is_redirection(shell, list) != 0 && (list->type >= 10 && list->type <= 16))
	{
		prep_redir_exec(shell, list);
		return (0);
	}
	if (list->type >= 10 && list->type <= 16)
		shell->last_return_value = execute_builtin(shell, list);
	else
	{
		if (pipe(fd) == -1)
			free_exit(shell, 1);
		pid = fork();
		if (pid < 0)
			free_exit(shell, 1);
		if (pid == 0)
		{
			if (is_redirection(shell, list) != 0)
			{
				prep_redir_exec(shell, list);
				return (0);
			}
			execute_binary(shell, list);
			exit (0);
		}
		else
		{
			wait(NULL);
			return (0);
		}
	}
	return (0);
}

int	execute(t_shell *shell)
{
	int		i;

	i = 0;
	if (shell->lists[1] == NULL)
		return (execute_no_pipe(shell, shell->lists[0]));
	forkex(shell);
	return (0);
}

