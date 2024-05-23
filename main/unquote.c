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
	free(str);
	tmp[i - 1] = 0;
	return (tmp);
}

int	unquote(t_shell *shell)
{
	int		i;
	int		n;
	int		tmp;
	int		flag;
	t_list	*ptr;

	i = 0;
	tmp = 0;
	flag = 0;
	if (!shell->lists)
		return (1);
	ptr = shell->lists[i];
	while (ptr)
	{
		n = 0;
		while (ptr->content[n])
		{
			tmp = n;
			set_flag(&ptr->content[n], &flag);
			if ((flag == 1 && ptr->content[n] == '\'') ||
				(flag == 2 && ptr->content[n] == '\"') ||
				(flag == 0 && ptr->content[n] == '\'') ||
				(flag == 0 && ptr->content[n] == '\"'))
			{
				while (ptr->content[tmp])
				{
					ptr->content[tmp] = ptr->content[tmp + 1];
					tmp++;
				}
				continue;
			}
			n++;
		}
		ptr = ptr->next;
		if (!ptr)
			ptr = shell->lists[++i];
	}
	return (0);
}
