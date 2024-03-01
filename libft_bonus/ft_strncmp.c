/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:09:56 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/07 17:09:58 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
/*
int	main(void)
{
	printf("%d \n", strncmp("Helao", "Hesbthis", 2));
	printf("%d \n", ft_strncmp("Helbo", "Hesathis", 2));
	printf("%d \n", strncmp("test\200", "test\0", 6));
	printf("%d", ft_strncmp("test\200", "test\0", 6));
	return (0);
}
*/
