/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:39:31 by kbrauer           #+#    #+#             */
/*   Updated: 2024/04/19 14:36:31 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

t_list	*ft_lstnew(char *str, int *k, t_shell *shell)
{
	t_list	*start;
	int		i;
	int		flag;

	if (!str)
		return (NULL);
	start = (t_list *) malloc (sizeof(t_list));
	if (!start)
		return (NULL);
	flag = 0;
	//while a delimiter
	str = while_del(str);
	//check if str starts with a "-sign or '-sign
	set_flag(&str[0], &flag);
	//while NOT a delimiter, count str length
	i = while_not_del(str, &flag, shell, k);
	start->content = (char *) malloc (sizeof(char) * (i + 1));
	if (!start->content)
		return (NULL);
	i = 0;
	set_flag(&str[0], &flag);
	while (str[i] && (check_del(str[i], flag) == 0) && str[i] != '\n')
	{
		start->content[i] = str[i];
		i++;
		set_flag(&str[i], &flag);
	}
	start->content[i] = '\0';
	start->next = NULL;
	return (start);
}

void	ft_lstadd_back(t_list *lst, t_list *new)
{
	t_list	*ptr;

	ptr = lst;
	if (lst)
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
		ptr = NULL;
	}
	else
		lst = new;
}

//check if chr equals one of the DEL (delimiters)
int	check_del(char	chr, int flag)
{
	int	i;

	i = 0;
	if (flag)
		return (0);
	while (DEL[i])
	{
		if (chr == DEL[i])
			return (1);
		i++;
	}
	return (0);
}