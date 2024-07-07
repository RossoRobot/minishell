/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:55:16 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/06 16:55:18 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/builtins.h"

static int	exit_hyper_helper(t_shell *shell, char *str)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp3 = ft_itoa(shell->h_lines);
	tmp = ft_strjoin(shell, "minishell: warning: here-document at line ",
			tmp3);
	free(tmp3);
	tmp2 = ft_strjoin(shell, tmp, " delimited by end-of-file (wanted `");
	free(tmp);
	tmp = ft_strjoin(shell, tmp2, str);
	free(tmp2);
	tmp2 = ft_strjoin(shell, tmp, "')\n");
	ft_putstr_fd(tmp2, 2);
	free(tmp);
	free(tmp2);
	return (0);
}

int	exit_helper(t_shell *shell, char *str, int flag)
{
	char	*tmp;
	char	*tmp2;

	if (flag == 0)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (flag == 1)
	{
		tmp = ft_strjoin(shell, "exit\nminishell: exit: ", str);
		tmp2 = ft_strjoin(shell, tmp, ": numeric argument required\n");
		ft_putstr_fd(tmp2, 2);
		free(tmp);
		free(tmp2);
		return (0);
	}
	else if (flag == 2)
	{
		exit_hyper_helper(shell, str);
	}
	return (0);
}
