/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:08:44 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/21 10:00:00 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

t_list	*free_parse_helper(t_list *ptr, char *content, t_list *list)
{
	if (content)
		free(content);
	if (list)
		free(list);
	return (ptr);
}

void	free_parse(t_shell *shell)
{
	int		i;
	t_list	*ptr;

	i = 0;
	if (!shell)
		return ;
	if (shell->lists)
	{
		if (shell->lists[i])
		{
			while (shell->lists[i])
			{
				ptr = shell->lists[i];
				while (ptr)
				{
					ptr = ptr->next;
					shell->lists[i] = free_parse_helper(ptr,
							shell->lists[i]->content, shell->lists[i]);
				}
				i++;
			}
		}
		free(shell->lists);
	}
	free_to_null(&shell->exp_str);
}

void	free_to_null(char **var)
{
	if (*var)
	{
		free(*var);
		*var = NULL;
	}
}

void	free_hname(t_shell *shell)
{
	t_hname	*ptr1;
	t_hname	*ptr2;

	ptr1 = shell->hname;
	ptr2 = shell->hname;
	while (ptr1)
	{
		ptr1 = ptr1->next;
		unlink(ptr2->content);
		if (ptr2->content)
			free(ptr2->content);
		if (ptr2)
			free(ptr2);
		ptr2 = ptr1;
	}
	shell->hname = NULL;
}

void	free_hname2(t_shell *shell)
{
	t_hname	*ptr1;
	t_hname	*ptr2;

	ptr1 = shell->hname;
	ptr2 = shell->hname;
	while (ptr1)
	{
		ptr1 = ptr1->next;
		if (ptr2->content)
			free(ptr2->content);
		if (ptr2)
			free(ptr2);
		ptr2 = ptr1;
	}
	shell->hname = NULL;
}
