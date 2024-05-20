/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:35:21 by kbrauer           #+#    #+#             */
/*   Updated: 2024/05/20 16:35:25 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	execute_echo(t_shell *shell, t_list *list)
{
	t_list	*ptr;
	int		flag;

	flag = 0;
	ptr = list->next;
	while (ptr)
	{
		if (ptr->type == flag_a)
		{
			flag = 1;
			ptr = ptr->next;
			continue;
		}
		printf("%s", ptr->content);
		ptr = ptr->next;
		if (ptr)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	return (0);
}
