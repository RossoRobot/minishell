/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:35:21 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/20 13:09:59 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

static void	skip_redirection(t_list *ptr)
{
	while (ptr->type == 4 || ptr->type == 5 || ptr->type == 7
		|| ptr->type == 17)
	{
		if (ptr->type == 4 || ptr->type == 5 || ptr->type == 7)
		{
			if (ptr->next && ptr->next->next)
				ptr = ptr->next->next;
		}
		else if (ptr->type == 17 && ptr->next)
			ptr = ptr->next;
	}
}

int	execute_echo(t_shell *shell, t_list *list)
{
	t_list	*ptr;
	int		flag;
	t_shell	*dummy;

	dummy = shell;
	flag = 0;
	ptr = list->next;
	print_tokens(shell);
	while (ptr && ptr->type == flag_a)
	{
		flag = 1;
		ptr = ptr->next;
	}
	while (ptr)
	{
		if (ptr->type == 4 || ptr->type == 5 || ptr->type == 7)
			skip_redirection(ptr);
		printf("%s", ptr->content);
		ptr = ptr->next;
		if (ptr)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	return (0);
}

void	handle_shlvl(t_shell *data)
{
	char	*str;
	char	*value;

	str = NULL;
	value = NULL;
	str = my_getenv(data, "SHLVL", 0);
	if (!str)
		export_malloc(data, ft_strdup(data, "SHLVL=0"), NULL, NULL);
	else
		free(str);
}