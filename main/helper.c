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
