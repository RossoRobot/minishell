/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:38:38 by kbrauer           #+#    #+#             */
/*   Updated: 2024/06/14 10:38:39 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	first_init(t_shell *shell)
{
	shell->exp_str = NULL;
	shell->env_line = NULL;
	shell->hname = NULL;
	shell->h_lines = 0;
	return (0);
}

int	init_values(t_shell *shell)
{
	shell->env_arr = NULL;
	shell->lists = NULL;
	shell->last_return_value = 0;
	shell->n_pipes = 0;
	shell->pids = NULL;
	return (0);
}
