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
	while (*str && (chk_del(shell, str, &zero, -1) == 1))
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
	while (str[i] && (chk_del(shell, &str[i], flag, i) == 0)
		&& str[i] != '\n')
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

int	pipe_error(t_shell *shell, char *str, int i)
{
	if (str[i] && str[i + 1] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|", 2);
		if (str[i + 1] && str[i + 2] == '|')
			ft_putstr_fd("|", 2);
		ft_putstr_fd("'\n", 2);
		return (set_return_value(shell, 2), 1);
	}
	return (0);
}
