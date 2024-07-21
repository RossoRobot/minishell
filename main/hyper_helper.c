/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:26:23 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/21 19:26:24 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	set_here_del_type(t_shell *shell)
{
	t_list	*ptr;
	int		i;

	i = 0;
	if (!shell->lists)
		return ;
	ptr = shell->lists[i];
	while (ptr)
	{
		if (ptr->type == he_doc && ptr->next)
			ptr->next->type = here_del;
		ptr = ptr->next;
		if (!ptr)
			ptr = shell->lists[++i];
	}
	ptr = NULL;
}
