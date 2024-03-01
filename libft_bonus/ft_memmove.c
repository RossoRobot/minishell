/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:20:48 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/05 15:20:54 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*d;
	const char		*s;

	i = -1;
	d = dest;
	s = src;
	if (dest < src)
	{
		while (++i != n)
			d[i] = s[i];
	}
	if (dest > src)
	{
		i = n;
		if (n == 0)
			i++;
		while (--i != 0)
		{
			d[i] = s[i];
		}
		if (n != 0)
			d[i] = s[i];
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
	ft_memmove(destination, source, 0);
	printf("%s", destination);
	return 0;
}

int	main(void)
{
	int source[] = {1, -2, 3};
	int destination[] = {0, 0, 0};
	printf("%d\n", source[1]);
	printf("%d\n", destination[1]);
	ft_memmove(destination, source, 12);
	printf("%d", destination[1]);
	return 0;
}
*/
