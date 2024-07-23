/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:39:19 by kbrauer           #+#    #+#             */
/*   Updated: 2024/06/19 16:39:22 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	set_exp_str(t_shell *shell, char *tmp)
{
	if (!ft_strncmp(tmp, "?", 2))
	{
		shell->exp_str = my_getenv(shell, "lrv", 0);
		free(tmp);
	}
	else
		shell->exp_str = my_getenv(shell, tmp, 1);
}

int	del_empty_tk(t_shell *shell)
{
	int		i;
	int		n;
	t_list	*ptr;

	i = 0;
	ptr = shell->lists[i];
	while (ptr)
	{
		n = 0;
		while(ptr)
		{
			if (!ptr->content[0] && !n)
			{
				ptr = del_first_node(shell, i, ptr);
				if (!ptr)
					ptr = shell->lists[++i];
				continue ;
			}
			n++;
			if (ptr->next && !ptr->next->content[0] && n)
				del_next_node(ptr);
			ptr = ptr->next;
		}
		if (!n)
		{
			re_mal_list(shell, i - 1);
			//ptr = shell->lists[i];
			if (shell->n_pipes)
				shell->n_pipes--;
		}
		else
			ptr = shell->lists[++i];
	}
	if (!shell->lists)
		return (1);
	return (0);
}

void	re_mal_list(t_shell *shell, int i)
{
	t_list	**new_list;
	int		n;
	int		m;
	int		c;

	set_data(&n, &m, &c, shell);
	c = shell->n_pipes;
	new_list = malloc (shell->n_pipes + 1);
	if (!new_list)
		free_parse(shell);
	while(c + 1)
	{
		if (m == i)
			m++;
		new_list[n] = shell->lists[m];
		n++;
		m++;
		c--;
	}
	free(shell->lists);
	shell->lists = new_list;
}

t_list	*del_first_node(t_shell *shell, int i, t_list *ptr)
{
	t_list	*tmp;

	tmp = ptr;
	shell->lists[i] = shell->lists[i]->next;
	free(tmp->content);
	free(tmp);
	return (shell->lists[i]);
}
