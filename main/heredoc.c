/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:20:17 by kbrauer           #+#    #+#             */
/*   Updated: 2024/05/17 14:20:18 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

char	*hedoc(t_shell *shell, t_list *node)
{
	int		fd;
	int		flag;
	char	*cmd;
	char	*new;

	flag = 0;
	fd = open("test.txt", O_RDWR | O_CREAT , 0644);
	while (1)
	{
		cmd = readline("> ");
		if (ft_strncmp(cmd, node->next->content, ft_strlen(cmd) + 1) == 0)
			break ;
		if (flag == 0)
			new = cmd;
		else
			new = ft_strjoin(shell, "\n", cmd);
		write(fd, new, ft_strlen(new));
		free(cmd);
		flag = 1;
	}
	return ("test.txt");
}

void	start_heredoc(t_shell *shell)
{
	t_list	*ptr;
	int		i;
	char 	*buf;

	buf = (char *)malloc(sizeof(char) * (99));
	buf[99] = 0;

	i = 0;
	ptr = shell->lists[i];
	while (ptr)
	{
		while (ptr)
		{
			if (ptr->type == he_doc)
			{
				read(open(hedoc(shell, ptr), O_RDONLY), buf, 99);
				printf("%s\n", buf);
				if (buf)
					free(buf);
				unlink("test.txt");
			}
			ptr = ptr->next;
		}
		i++;
		ptr = shell->lists[i];
	}
}
