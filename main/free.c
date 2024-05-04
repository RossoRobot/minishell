/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:08:44 by kbrauer           #+#    #+#             */
/*   Updated: 2024/04/22 17:43:10 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	free_parse(t_shell *shell)
{
	int		i;
	t_list	*ptr;

	i = 0;
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
					if (shell->lists[i]->content)
						free(shell->lists[i]->content);
					if (shell->lists[i])
						free(shell->lists[i]);
					shell->lists[i] = ptr;
				}
				i++;
			}
		}
		free(shell->lists);
	}
	if (shell->exp_str)
		free_to_null(&shell->exp_str);
}

void	free_to_null(char **var)
{
	free(*var);
	*var = NULL;
}