/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_return_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:58:32 by kbrauer           #+#    #+#             */
/*   Updated: 2024/06/15 14:58:35 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	set_return_value(t_shell *shell, int retval)
{
	char	*retval_str;


	shell->last_return_value = retval;
	retval_str = ft_itoa(retval);
	if (!retval_str)
		return (-1);
	replace_var(shell, "?", retval_str, 0);
	return (retval);
}

int	increase_flag(char c, char d)
{
	if (c == d)
		return (1);
	return (0);
}
