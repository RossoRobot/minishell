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

int	del_empty_tk(t_shell *shell, int i)
{
	t_list	*ptr;
	int		n;

	while (shell->lists[i])
	{
		ptr = shell->lists[i];
		n = 0;
		loopyloop(shell, ptr, i, &n);
		if (!shell->lists[i])
			create_null_node(shell, i);
		i++;
	}
	return (0);
}

t_list	*del_first_node(t_shell *shell, int i, t_list *ptr)
{
	t_list	*tmp;

	tmp = ptr;
	shell->lists[i] = shell->lists[i]->next;
	free(tmp->content);
	free(tmp);
	return (shell->lists[i]);
}

void	set_null_type(t_shell *shell)
{
	int		i;
	t_list	*ptr;

	i = 0;
	ptr = shell->lists[i];
	while (ptr)
	{
		while (ptr)
		{
			if (!ptr->content[0])
				ptr->type = null_a;
			ptr = ptr->next;
		}
		ptr = shell->lists[++i];
	}
}

int	check_pipe_red(t_shell *shell, char *str)
{
	if (start_w_pipe(shell, str))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		write(2, "||", start_w_pipe(shell, str));
		write(2, "'\n", 2);
		return (set_return_value(shell, 2), 1);
	}
	if (correct_red(str) && start_w_red(str))
	{
		ft_putstr_fd("minishell: syntax error near \
unexpected token `newline'\n", 2);
		return (set_return_value(shell, 2), 1);
	}
	return (0);
}
