/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_env_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:59:45 by kbrauer           #+#    #+#             */
/*   Updated: 2024/06/15 11:59:46 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	squeeze_node(t_list *ptr, char *content)
{
	t_list	*new_node;
	t_list	*tmp;

	new_node = malloc (sizeof(t_list));
	if (!new_node)
		return (0);
	tmp = ptr->next;
	ptr->next = new_node;
	new_node->next = tmp;
	new_node->content = content;
	return (0);
}

int	split_token(t_list *ptr, int n)
{
	int		i;
	int		flag;
	char	*new_str;

	i = ft_strlen(&ptr->content[n + 1]);
	flag = 0;
	new_str = malloc (sizeof(char) * (i + 1));
	if (!new_str)
		return (0);
	i = 0;
	while (ptr->content[n])
	{
		new_str[i++] = ptr->content[n + 1];
		ptr->content[n++] = 0;
	}
	squeeze_node(ptr, new_str);
	return (0);
}

int	sep_env_cmd(t_shell *shell)
{
	int		i;
	int		n;
	int		flag;
	t_list	*ptr;

	i = 0;
	n = 0;
	flag = 0;
	ptr = shell->lists[i];
	while (ptr)
	{
		n = 0;
		while (ptr->content[n])
		{
			set_flag(&ptr->content[n], &flag);
			if (ptr->content[n] == ' ' && flag == 0)
				split_token(ptr, n);
			n++;
		}
		ptr = ptr->next;
		if (!ptr)
			ptr = shell->lists[++i];
	}
	return (0);
}

void	negative_fd(t_shell *shell, int fd)
{
	if (fd == -1)
	{
		ft_putstr_fd("open() failed\n", 2);
		free_exit(shell, 1);
	}
}

void	newl_numl(int *flag, int fd, int *num_lines, char *cmd)
{
	if (*flag != 0)
		write(fd, "\n", 1);
	*flag = 1;
	*num_lines += write_free(fd, &cmd);
}
