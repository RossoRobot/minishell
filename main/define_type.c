/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:12:43 by kbrauer           #+#    #+#             */
/*   Updated: 2024/04/19 14:36:07 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"


int	set_type(t_list *node)
{
	if (!strncmp(node->content, "echo", 10))
		node->type = echo_a;
	else if (!strncmp(node->content, "cd", 10))
		node->type = cd_a;
	else if (!strncmp(node->content, "pwd", 10))
		node->type = pwd_a;
	else if (!strncmp(node->content, "export", 10))
		node->type = export_a;
	else if (!strncmp(node->content, "unset", 10))
		node->type = unset_a;
	else if (!strncmp(node->content, "env", 10))
		node->type = env_a;
	else if (!strncmp(node->content, "exit", 10))
		node->type = exit_a;
	else
		node->type = command_a;
	return (set_type2(node));
}

int	set_type2(t_list *node)
{
	if (!strncmp(node->content, ">", 10))
		node->type = metachar_a;
	else if (!strncmp(node->content, ">>", 10))
		node->type = metachar_a;
	else if (!strncmp(node->content, "<", 10))
		node->type = metachar_a;
	else if (!strncmp(node->content, "<<", 10))
		node->type = metachar_a;
	return (0);
}

void    define_type(t_shell *shell)
{
	t_list	*ptr;
	int		i;

	i = 0;
	while (shell->lists[i])
	{
		ptr = shell->lists[i];
		set_type(ptr);
		if (!strncmp(ptr->content, "echo", 10) &&
			!strncmp(ptr->next->content, "-n", 10))
		{
			ptr = ptr->next;
			ptr->type = flag_a;
		}
		ptr = ptr->next;
		while (ptr)
		{
			ptr->type = text_a;
			set_type2(ptr);
			ptr = ptr->next;
		}
		i++;
	}
	ptr = NULL;
}