/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:20:17 by kbrauer           #+#    #+#             */
/*   Updated: 2024/05/28 18:13:21 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

char	*add_hname(t_shell *shell)
{
	char	*buf;
	char	*name;
	
	buf = (char *) malloc (sizeof(char) * 11);
	read(open("/dev/urandom", O_RDONLY), buf, 10);
	buf[10] = 0;
	name = ft_strjoin(shell, buf, ".txt");
	free(buf);
	if (!shell->hname)
		shell->hname = ft_lstnew_hdoc(shell, name);
	else
		ft_lstadd_back_hdoc(shell->hname, ft_lstnew_hdoc(shell, name));
	//printf("%s\n", name);
	return (name);
}

char	*here_doc(t_shell *shell, char *arg)
{
	int		fd;
	int		flag;
	char	*cmd;
	char	*hname;

	//create random name
	hname = add_hname(shell);
	flag = 0;
	fd = open(hname, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		cmd = readline("> ");
		if (!cmd)
			break ;
		if (ft_strncmp(cmd, arg, ft_strlen(cmd) + 1) == 0)
		{
			write(fd, "\n", 1);
			free(cmd);
			break ;
		}
		if (flag++ != 0)
			write(fd, "\n", 1);
		write(fd, cmd, ft_strlen(cmd));
		free(cmd);
	}
	return (hname);
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
	char 	*tmp;
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
				if (!ptr->next)
				{
					ft_putstr_fd("syntax error near unexpected token `newline'\n" ,2);
					return (1);
				}
				tmp = ft_strdup(shell, here_doc(shell, ptr->next->content));
				free(ptr->content);
				ptr->content = tmp;
				ptr->type = text_a;
				del_next_node(ptr);
				if (ptr->next)
					if (ptr->next->type == he_doc)
						ptr->type = delete_a;
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

