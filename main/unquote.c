/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:53:24 by kbrauer           #+#    #+#             */
/*   Updated: 2024/05/09 14:53:27 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

char	*del_quote(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
		i++;
	tmp = (char *) malloc (sizeof(char) * (i - 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i + 1])
	{
		tmp[i] = str[i + 1];
		i++;
	}
	tmp[i - 1] = 0;
	return (tmp);
}

void	unquote(t_shell *shell)
{
	int		i;
	t_list	*ptr;

	i = 0;
	ptr = shell->lists[i];
	while (ptr)
	{
		if (ptr->content[0] == '\'' || ptr->content[0] == '\"')
		{
			ptr->content = del_quote(ptr->content);
		}
		ptr = ptr->next;
		if (!ptr)
			ptr = shell->lists[++i];
	}
}
