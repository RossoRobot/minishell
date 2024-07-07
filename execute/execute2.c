/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:45:52 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/06 18:51:34 by mvolgger         ###   ########.fr       */
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

static void	check_hdocs(t_shell *shell, char *str)
{
	int		i;
	t_hname	*temp;

	i = 0;
	temp = shell->hname;
	while (temp)
	{
		if (!ft_strncmp(str, temp->content, ft_strlen(str)))
		{
			free(str);
			free_exit(shell, 1);
		}
		temp = temp->next;
	}
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
	check_hdocs(shell, path);
	argv = trans_argv(shell, list);
	shell->sig_flag = true;
	recieve_signal(shell, 0, 0);
	if (execve(path, argv, shell->env_arr) == -1)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(path);
		free_arr(argv);
		free_exit(shell, 0);
		exit(127);
	}
	recieve_signal(shell, 2, 0);
	return (0);
}

int	check_last_node(t_list *list, int flag)
{
	t_list	*temp;

	temp = list;
	while (temp->next)
		temp = temp->next;
	if (!ft_strncmp(temp->content, "<", ft_strlen(temp->content))
		|| !ft_strncmp(temp->content, "<<", ft_strlen(temp->content))
		|| !ft_strncmp(temp->content, ">>", ft_strlen(temp->content))
		|| !ft_strncmp(temp->content, ">", ft_strlen(temp->content)))
	{
		if (flag == 1)
		{
			ft_putstr_fd("minishell: syntax error near ", 2);
			ft_putstr_fd("unexpected token `newline'\n", 2);
		}
		else
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
				2);
		}
		return (1);
	}
	return (0);
}
