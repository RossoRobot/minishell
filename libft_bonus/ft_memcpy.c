/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:45:35 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/05 14:45:37 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*d;
	const char		*s;

	i = 0;
	d = dest;
	s = src;
	if (src == dest || n == 0)
		return (dest);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return ((void *)d);
}
/*
int	main(void)
{
	const char source[] = "This is source again";
	char destination[7];
	printf("%s\n", source);
	printf("%s\n", destination);
	ft_memcpy(destination, source, 7);
	printf("%s", destination);
	return 0;
}

int	main(void)
{
	int source[] = {1, 2, 3};
	int destination[] = {0, 0, 0};
	printf("%d\n", source[2]);
	printf("%d\n", destination[2]);
	ft_memcpy(destination, source, 12);
	printf("%d", destination[2]);
	return 0;
}
*/
