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

int	del_empty_tk(t_shell *shell, int i)
{
	t_list	*ptr;

	while (shell->lists[i])
	{
		ptr = shell->lists[i];
		while(ptr)
		{
			if (ptr->type >= 4 && ptr->type <= 7)
			{
				ptr = ptr->next;
				if (!ptr)
					break;
				ptr = ptr->next;
				continue ;
			}
			if (ptr->next && ptr->next->type == null_a)
			{
				del_next_node(ptr);
				continue ;
			}
			ptr = ptr->next;
		}
		i++;
	}
	return (0);
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

void set_null_type(t_shell *shell)
{
	int		i;
	t_list	*ptr;

	i = 0;
	ptr = shell->lists[i];
	while (ptr)
	{
		while(ptr)
		{
			if (!ptr->content[0])
				ptr->type = null_a;
			ptr = ptr->next;
		}
		ptr = shell->lists[++i];
	}
}
