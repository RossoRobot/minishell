/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:50:21 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/21 19:48:52 by mvolgger         ###   ########.fr       */
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
