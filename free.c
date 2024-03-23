/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:08:44 by kbrauer           #+#    #+#             */
/*   Updated: 2024/03/23 16:08:49 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_all(t_shell *shell)
{
    int     i;
    t_list  *ptr;

    i = 0;
    if (shell->lists)
    {
        while (shell->lists[i])
        {
            ptr = shell->lists[i];
            while (ptr)
            {
                ptr = ptr->next;
                free(shell->lists[i]->content);
                free(shell->lists[i]);
                shell->lists[i] = ptr;
            }
            i++;
        }
        free(shell->lists);
    }
}