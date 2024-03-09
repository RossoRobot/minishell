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

t_list	*ft_lstnew(char *content)
{
	t_list	*start;

	start = (t_list *) malloc (sizeof(t_list));
	if (!start)
		return (NULL);
	start->content = content;
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

