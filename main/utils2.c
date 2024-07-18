/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:27:51 by kbrauer           #+#    #+#             */
/*   Updated: 2024/04/19 12:00:48 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

char	*skip_gap(char *str)
{
	while ((*str == 9 || *str == 10 || *str == 32) && *str)
		str++;
	return (str);
}

char	*while_del(t_shell *shell, char *str)
{
	int	zero;

	zero = 0;
	while (*str && (check_del(shell, str, &zero, -1) == 1))
		str++;
	return (str);
}

int	while_not_del(char *str, int *flag, t_shell *shell, int *k)
{
	int		i;
	int		exp;
	int		len;
	t_shell	*ptr;

	ptr = shell;
	i = 0;
	exp = 0;
	len = 0;
	while (str[i] && (check_del(shell, &str[i], flag, i) == 0) && str[i] != '\n')
	{
		i++;
		set_flag(&str[i], flag);
	}
	*k = i;
	return (i + exp - len);
}

void	set_flag(char *c, int *flag)
{
	if (*flag == 0 && *c == '\'')
	{
		*flag = 1;
		return ;
	}
	else if (*flag == 0 && *c == '\"')
	{
		*flag = 2;
		return ;
	}
	if (*flag == 1 && *c == '\'')
	{
		*flag = 0;
		return ;
	}
	else if (*flag == 2 && *c == '\"')
	{
		*flag = 0;
		return ;
	}
}
