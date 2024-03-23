/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:35:39 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/07 18:35:42 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int		i;
	unsigned char		*str1;
	unsigned char		*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < (n - 1) && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}
/*
int	main(void)
{
	char	s1[] = {-2, 0, 2, 0};
	char	s2[] = {0, 0, 0, -1};
	printf("%d \n", memcmp("Helao", "Iesbthis", 1));
	printf("%d \n", ft_memcmp("Helbo", "Iesathis", 1));
	printf("%d \n", memcmp(s1, s2, 1));
	printf("%d", ft_memcmp(s1, s2, 1));
	return (0);
}
*/
