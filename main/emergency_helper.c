/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emergency_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:55:19 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/29 17:55:22 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	maybe_del_next(t_list *ptr)
{
	if (ptr->next && ptr->next->type == null_a)
	{
		del_next_node(ptr);
		return (1);
	}
	return (0);
}

int	loopyloop(t_shell *shell, t_list *ptr, int i, int *n)
{
	while (ptr)
	{
		if (ptr->type == null_a && *n == 0)
		{
			ptr = del_first_node(shell, i, ptr);
			continue ;
		}
		*n = 1;
		if (ptr->type >= 4 && ptr->type <= 7)
		{
			ptr = ptr->next;
			if (!ptr)
				break ;
			ptr = ptr->next;
			continue ;
		}
		if (maybe_del_next(ptr))
			continue ;
		ptr = ptr->next;
	}
	return (0);
}
