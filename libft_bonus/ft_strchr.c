/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:12:04 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/07 16:12:07 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		else
			i++;
	}
	if ((unsigned char)c == 0)
		return ((char *)&s[i]);
	else
		return (0);
}
/*
int	main(void)
{
	char string[] = "12345";
	int	chr = '3' + 256;
	printf("%s\n", strchr(string, chr));
	printf("%s", ft_strchr(string, chr));
}
*/
