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
	new_node->type = text_a;
	return (0);
}

int	split_token(t_list *ptr)
{
	int		i;
	char	**arr;

	arr = ft_split(ptr->content, ' ');
	if (!arr)
		return (1);
	i = -1;
	while (ptr->content[++i])
	{
		if (ptr->content[i] == ' ')
		{
			ptr->content[i] = 0;
			break ;
		}
	}
	i = 1;
	while (arr[i])
	{
		squeeze_node(ptr, arr[i]);
		ptr = ptr->next;
		i++;
	}
	free(arr[0]);
	free(arr);
	return (0);
}

int	sep_env_cmd(t_shell *shell)
{
	int		i;
	int		n;
	int		flag;
	t_list	*ptr;

	set_data(&i, &n, &flag, shell);
	ptr = shell->lists[i];
	while (ptr)
	{
		n = 0;
		while (ptr->content[n])
		{
			set_flag(&ptr->content[n], &flag);
			if (ptr->content[n++] == ' ' && flag == 0)
			{
				if (split_token(ptr))
					free_exit(shell, 1);
			}
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
