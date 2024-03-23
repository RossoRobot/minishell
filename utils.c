/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:39:31 by kbrauer           #+#    #+#             */
/*   Updated: 2024/03/09 18:49:09 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(char *str)
{
	t_list	*start;
	int		i;

	start = (t_list *) malloc (sizeof(t_list));
	if (!start)
		return (NULL);
	i = 0;
	//while not a delimiter
	while (str[i] && (check_del(str[i]) == 0))
		i++;
	start->content = (char *) malloc (sizeof(char) * (i + 1));
	if (!start->content)
		return (NULL);
	i = 0;
	while (str[i] && (check_del(str[i]) == 0))
	{
		start->content[i] = str[i];
		i++;
	}
	start->content[i] = '\0';
	start->type = text;
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < (n - 1) && s1[i] == s2[i] && s1[i] != 0)
		i++;
	if (n == 0)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

//check if chr equals one of the DEL (delimiters)
int	check_del(char	chr)
{
	int	i;

	i = 0;
	while (DEL[i])
	{
		if (chr == DEL[i])
			return (1);
		i++;
	}
	return (0);
}