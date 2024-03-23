/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:52:56 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/07 16:52:59 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			j = i;
		i++;
	}
	if ((unsigned char)c == 0)
		return ((char *)&s[i]);
	else if (j == -1)
		return (0);
	else
		return ((char *)&s[j]);
}
/*
int	main(void)
{
	char string[] = "12345";
	int	chr = '3';
	printf("%s\n", strrchr(string, chr));
	printf("%s", ft_strrchr(string, chr));
}
*/
