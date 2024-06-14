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

int	check_for_quote(int flag, char c, int tmp, char *content)
{
	if ((flag == 1 && c == '\'')
		|| (flag == 2 && c == '\"')
		|| (flag == 0 && c == '\'')
		|| (flag == 0 && c == '\"'))
	{
		while (content[tmp])
		{
			content[tmp] = content[tmp + 1];
			tmp++;
		}
		return (1);
	}
	return (0);
}

t_list	**set_data(int *i, int *tmp, int *flag, t_shell *shell)
{
	if (i)
		*i = 0;
	if (tmp)
		*tmp = 0;
	if (flag)
		*flag = 0;
	return (shell->lists);
}

int	unquote(t_shell *shell)
{
	int		i;
	int		n;
	int		tmp;
	int		flag;
	t_list	*ptr;

	if (!set_data(&i, &tmp, &flag, shell))
		return (1);
	ptr = shell->lists[i];
	while (ptr)
	{
		n = 0;
		while (ptr->content[n])
		{
			tmp = n;
			set_flag(&ptr->content[n], &flag);
			if (check_for_quote(flag, ptr->content[n], tmp, ptr->content))
				continue ;
			n++;
		}
		ptr = ptr->next;
		if (!ptr)
			ptr = shell->lists[++i];
	}
	return (0);
}
