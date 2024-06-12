/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:38:55 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/12 13:29:37 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/builtins.h"
#include "./../include/minishell.h"

int	execute_export(t_shell *shell, t_list *list)
{
	t_list	*temp;

	temp = list;
	if (temp->next == NULL)
		return (export(shell, NULL, NULL, NULL));
	while (temp->next != NULL)
	{
		export(shell, temp->next->content, NULL, NULL);
		temp = temp->next;
	}
	return (0);
}

int	execute_env(t_shell *shell, t_list *list)
{
	if (list->next)
	{
		if (list->next->content[0] == '-')
		{
			ft_putstr_fd("env: invalid option '", 2);
			ft_putstr_fd(list->next->content, 2);
			ft_putstr_fd("'\n", 2);
		}
		else
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(list->next->content, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		return (-1);
	}
	print_myenv(shell, 0);
	return (0);
}

int	execute_unset(t_shell *shell, t_list *list)
{
	while (list->next != NULL)
	{
		unset(shell, list->next->content);
		list = list->next;
	}
	return (0);
}

int	execute_cd(t_shell *shell, t_list *list)
{
	char	*str;

	str = NULL;
	if (list->next && list->next->next)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (-1);
	}
	if (!list->next)
		return (change_directory(shell, NULL));
	else
	{
		str = ft_strdup(shell, list->next->content);
		return (change_directory(shell, str));
	}
}
