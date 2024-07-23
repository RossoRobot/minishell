/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:50:21 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/23 21:42:39 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	print_error_msg(int err, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (err == EACCES)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (err == ENOENT)
		ft_putstr_fd(" : command not found\n", 2);
	else if (err == ENOEXEC)
		ft_putstr_fd(" : Exec format error\n", 2);
	else if (err == EISDIR)
		ft_putstr_fd(" : Is a directory\n", 2);
	else if (err == ETXTBSY)
		ft_putstr_fd(" : Text file busy\n", 2);
	else if (err == ENOMEM)
		ft_putstr_fd(" : Out of memory\n", 2);
	else
		ft_putstr_fd("execve failed\n", 2);
}

static int	check_for_slash(char *path)
{
	int	i;
	int	slashflag;

	i = 0;
	slashflag = 0;
	if (!path)
		return (0);
	while (path && path[i])
	{
		if (path[i] == '/')
			slashflag = 1;
		i++;
	}
	return (slashflag);
}

void	check_for_dir(t_shell *shell, char *path, char **ar)
{
	struct stat	path_stat;

	if (!check_for_slash(path))
		return ;
	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": is a directory.\n", 2);
		free_arr(ar);
		free(path);
		free_exit(shell, 126);
	}
	if (execve(path, ar, shell->env_arr) == -1)
	{
		print_error_msg(errno, path);
		free(path);
		free_arr(ar);
		free_exit(shell, 127);
	}
}
