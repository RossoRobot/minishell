/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:44:33 by kbrauer           #+#    #+#             */
/*   Updated: 2024/03/09 15:09:19 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*start;

	start = (t_list *) malloc (sizeof(t_list));
	if (!start)
		return (NULL);
	start->content = content;
	start->next = NULL;
	return (start);
}
