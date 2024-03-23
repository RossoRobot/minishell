/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:42:20 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/05 13:42:24 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = s;
	while (i != n)
	{
		str[i] = '\0';
		i++;
	}
}
/*
int	main(void)
{
	char str[] = "123v5s7a9";
	printf("%s\n", str);
	ft_bzero(str, 5);
	printf("%s\n", str);
	
	//bzero(str, 5);
	//printf("%s\n", str);
	return(0);	
}
*/
