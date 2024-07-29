/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:15:18 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/29 17:50:55 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

char	*path_access(t_shell *shell, t_list *list, char **arr)
{
	int		i;
	char	*temp;
	char	*cmd_path;

	i = 0;
	temp = NULL;
	while (arr[i])
	{
		temp = ft_strjoin(shell, arr[i], "/");
		cmd_path = ft_strjoin(shell, temp, list->content);
		free(temp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_strdup(shell, list->content));
}

char	*get_path(t_shell *shell, t_list *list)
{
	char	*path;
	char	*cmd;
	char	**path_arr;

	path = NULL;
	cmd = NULL;
	if (access(list->content, F_OK | X_OK) == 0)
		return (ft_strdup(shell, list->content));
	path = my_getenv(shell, "PATH", 0);
	if (path == NULL)
		return (ft_strdup(shell, list->content));
	path_arr = ft_split(path, ':');
	if (!path_arr)
	{
		free(path);
		free_exit(shell, 0);
	}
	cmd = path_access(shell, list, path_arr);
	free_arr(path_arr);
	free(path);
	return (cmd);
}

void	close_all_fds(void)
{
	int	fd;

	fd = 0;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

int	check_for_empty_cmd(t_shell *shell, t_list *list, int flag)
{
	t_list	*temp;

	temp = list;
	while (temp && temp->type == 19)
		temp = temp->next;
	if (!temp)
	{
		if (flag == 0)
		{
			set_return_value(shell, 0);
			return (127);
		}
		else
		{
			free_exit(shell, 0);
		}
	}
	return (0);
}

int	check_for_redirections(t_list *temp)
{
	if ((!ft_strncmp(temp->content, "<", ft_strlen(temp->content))
			|| !ft_strncmp(temp->content, "<<", ft_strlen(temp->content))
			|| !ft_strncmp(temp->content, ">>", ft_strlen(temp->content))
			|| !ft_strncmp(temp->content, ">", ft_strlen(temp->content)))
		&& (temp->type != text_a))
		return (1);
	return (0);
}
