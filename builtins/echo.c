/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:35:21 by kbrauer           #+#    #+#             */
/*   Updated: 2024/06/17 16:21:48 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	execute_echo(t_shell *shell, t_list *list)
{
	t_list	*ptr;
	int		flag;

	flag = 0;
	ptr = list->next;
	while (ptr && ptr->type == flag_a)
	{
		flag = 1;
		ptr = ptr->next;
	}
	while (ptr)
	{
		if (ptr->type == 4 || ptr->type == 5 || ptr->type == 7)
			break ;
		printf("%s", ptr->content);
		ptr = ptr->next;
		if (ptr)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	return (0);
}
