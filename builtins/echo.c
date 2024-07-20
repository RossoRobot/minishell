/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:35:21 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/20 15:55:16 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

static t_list	*skip_redirection(t_list *ptr, int *flag)
{
	while (ptr->type == 4 || ptr->type == 5 || ptr->type == 7)
	{
		ptr = ptr->next;
		if (ptr)
			ptr = ptr->next;
		if (!ptr)
			break ;
		while (ptr->type == flag_a)
		{
			*flag = 1;
			ptr = ptr->next;
		}
	}
	return (ptr);
}

static void	find_flag(t_list *node)
{
	int		flag_n;
	t_list	*ptr;

	flag_n = 0;
	ptr = node;
	while (ptr)
	{
		if (flag_n == 1 && !is_n_flag(ptr->content) && !(ptr->type == re_in
				|| ptr->type == re_out || ptr->type == out_app))
			break ;
		if (ptr->type == re_in || ptr->type == re_out || ptr->type == out_app)
		{
			ptr = ptr->next;
			if (!ptr)
				continue ;
		}
		else if (is_n_flag(ptr->content))
		{
			flag_n = 1;
			ptr->type = flag_a;
		}
		else if (!is_n_flag(ptr->content) && ptr->type == flag_a)
			ptr->type = text_a;
		ptr = ptr->next;
	}
}

static int	check_for_last_pos(t_list *ptr)
{
	if (!ptr)
		return (0);
	while (ptr)
	{
		if (ptr->type == 4 || ptr->type == 5 || ptr->type == 7)
		{
			ptr = ptr->next;
			if (ptr)
				ptr = ptr->next;
		}
		if (!ptr)
			return (0);
		if (ptr->type != 4 && ptr->type != 5 && ptr->type != 7)
			return (1);
	}
	return (0);
}

static t_list	*echo_loop(t_list *ptr, int *flag)
{
	while (ptr && ptr->type == flag_a)
	{
		*flag = 1;
		ptr = ptr->next;
	}
	return (ptr);
}

int	execute_echo(t_shell *shell, t_list *list)
{
	t_list	*ptr;
	int		flag;
	t_shell	*dummy;

	dummy = shell;
	flag = 0;
	ptr = list->next;
	find_flag(list);
	ptr = echo_loop(ptr, &flag);
	while (ptr)
	{
		if (ptr->type == 4 || ptr->type == 5 || ptr->type == 7)
			ptr = skip_redirection(ptr, &flag);
		if (ptr)
		{
			ft_putstr_fd(ptr->content, 1);
			ptr = ptr->next;
		}
		if (ptr && check_for_last_pos(ptr))
			ft_putstr_fd(" ", 1);
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}
