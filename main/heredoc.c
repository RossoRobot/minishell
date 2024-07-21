/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:20:17 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/21 16:53:08 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

char	*add_hname(t_shell *shell)
{
	char	*buf;
	char	*name;
	int		fd;

	buf = (char *) malloc (sizeof(char) * 11);
	fd = open("/dev/urandom", O_RDONLY);
	negative_fd(shell, fd);
	read(fd, buf, 10);
	buf[10] = 0;
	name = ft_strjoin(shell, buf, ".txt");
	free(buf);
	if (!shell->hname)
		shell->hname = ft_lstnew_hdoc(shell, name);
	else
		ft_lstadd_back_hdoc(shell->hname, ft_lstnew_hdoc(shell, name));
	close(fd);
	return (name);
}

char	*here_doc(t_shell *shell, char *arg)
{
	int		fd;
	int		flag;
	int		num_lines;
	char	*cmd;
	char	*hname;

	hname = add_hname(shell);
	set_flag_and_num_lines(&flag, &num_lines);
	fd = open(hname, O_RDWR | O_CREAT | O_TRUNC, 0644);
	negative_fd(shell, fd);
	if (shell->heredoc_flag == 1)
		return (check_g_var(shell, fd));
	while (1)
	{
		cmd = readline("> ");
		if (g_var == 2)
			return (free(cmd), set_return_value(shell, 130), check_g_var(shell, fd));
		if (cmd_is_null_or_del(cmd, fd, arg, shell))
		{
			count_lines_newl(shell, num_lines, flag, fd);
			break ;
		}
		newl_numl(&flag, fd, &num_lines, cmd);
	}
	return (g_var = 0, close (fd), hname);
}

void	del_next_node(t_list *ptr)
{
	t_list	*tmp;

	tmp = ptr->next->next;
	free(ptr->next->content);
	free(ptr->next);
	ptr->next = tmp;
}

int	start_heredoc(t_shell *shell)
{
	t_list	*ptr;
	char	*tmp;
	int		i;

	i = 0;
	if (!shell->lists)
		return (1);
	ptr = shell->lists[i];
	while (ptr)
	{
		while (ptr)
		{
			if (ptr->type == he_doc)
			{
				if (no_del(ptr))
					return (1);
				recieve_signal(shell, 0, 0, "0");
				tmp = ft_strdup(shell, here_doc(shell, ptr->next->content));
				heredoc_helper(shell, ptr->content, ptr, tmp);
			}
			ptr = ptr->next;
		}
		ptr = shell->lists[++i];
	}
	return (0);
}

void	trim_hedoc(t_shell *shell)
{
	t_list	*ptr;
	int		i;

	i = 0;
	ptr = shell->lists[i];
	while (ptr)
	{
		while (ptr)
		{
			if (ptr->next)
				if (ptr->next->type == delete_a)
					del_next_node(ptr);
			ptr = ptr->next;
		}
		ptr = shell->lists[++i];
	}
}
