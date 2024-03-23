/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:21:26 by kbrauer           #+#    #+#             */
/*   Updated: 2023/10/14 16:21:28 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*node;
	t_list	*new_lst;
	void	*cont;

	ptr = lst;
	if (!lst)
		return (NULL);
	new_lst = NULL;
	while (ptr)
	{
		cont = f(ptr->content);
		if (cont)
			node = ft_lstnew(cont);
		if (!cont || !node)
		{
			ft_lstclear(&new_lst, del);
			del(cont);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, node);
		ptr = ptr->next;
	}
	return (new_lst);
}
