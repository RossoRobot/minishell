/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:10:24 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/07 18:10:27 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int			i;
	unsigned const char		*str;
	unsigned char			chr;

	i = 0;
	str = s;
	chr = c;
	while (i < n)
	{
		if (str[i] == chr)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char string[] = {0, 1, 2, 3, 4, 5};
	int character = 2;
	printf("%s\n", memchr(string, character, 12));
	printf("%s", ft_memchr(string, character, 12));
}
*/
