/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:15:18 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/25 15:56:20 by mvolgger         ###   ########.fr       */
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
