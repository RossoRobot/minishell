/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:10:25 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/05 12:10:27 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, size_t c, int n)
{
	int				i;
	unsigned char	*s;

	i = 0;
	s = str;
	while (i != n)
	{
		s[i] = (unsigned char) c;
		i++;
	}
	return ((void *)&s[0]);
}
/*
int	main(void)
{
	char str[] = "123v5s7a9";
	unsigned char chrx = 'x';
	unsigned char chry = 'y';
	printf("%s\n", str);
	ft_memset(&str, chrx, 5);
	printf("%s\n", str);
	
	memset(str, chry, 5);
	printf("%s\n", str);
	return(0);	
}
*/
