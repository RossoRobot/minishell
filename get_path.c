/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:49:09 by codespace         #+#    #+#             */
/*   Updated: 2024/03/21 18:06:44 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char *cmd, char **envp)
{
	char	**path_arr;
	char	**clean_cmd;
	char	*path;
	char	*temp;

	path = NULL;
	temp = NULL;
	path_arr = ft_split(ft_grep(envp), ':');
	clean_cmd = ft_split(cmd, ' ');
	if (!path_arr || !clean_cmd)
		return (free_arr(path_arr), free_arr(clean_cmd), NULL);
	path = path_access(path_arr, clean_cmd, temp, path);
	free_arr(path_arr);
	free_arr(clean_cmd);
	return (path);
}

char	*path_access(char **path_array, char **clean_cmd, char *temp,
		char *path)
{
	int	i;

	i = 0;
	while (path_array[i])
	{
		temp = ft_strjoin(path_array[i], "/");
		if (!temp)
			return (NULL);
		path = ft_strjoin(temp, clean_cmd[0]);
		free(temp);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*ft_grep(char **envp)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = "PATH=";
	while (envp[i])
	{
		while (envp[i][j] && envp[i][j] != '=' && (envp[i][j] == str[j]))
			j++;
		if (str[j] == '=')
			return (envp[i]);
		j = 0;
		i++;
	}
	exit (-1);
}
