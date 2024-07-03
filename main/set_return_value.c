/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_return_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:58:32 by kbrauer           #+#    #+#             */
/*   Updated: 2024/06/19 15:32:16 by mvolgger         ###   ########.fr       */
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
	replace_var(shell, "lrv", retval_str, 0);
	free(retval_str);
	return (retval);
}

int	increase_flag(char c, int *f1, int *f2, int *ff)
{
	if (c == '\'' && *ff != 2)
	{
		*f1 += 1;
		if (*ff == 0)
			*ff = 1;
		else if (*ff == 1)
			*ff = 0;
	}
	if (c == '\"' && *ff != 1)
	{
		*f2 += 1;
		if (*ff == 0)
			*ff = 2;
		else if (*ff == 2)
			*ff = 0;
	}
	return (0);
}

void	pipe_counter(t_shell *s, char c, int f1, int f2)
{
	if (c == '|' && (!(f1 % 2) && !(f2 % 2)))
		s->n_pipes++;
}
