/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:15:23 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/08 17:15:26 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	slen;
	char			*ptr;

	i = 0;
	if (start > ft_strlen(s))
		slen = 0;
	else if (len < ft_strlen(s) - start)
		slen = len;
	else
		slen = (ft_strlen(s) - start);
	ptr = (char *)malloc(slen * sizeof(char) + 1);
	if (!ptr)
		return (0);
	while (i < slen)
	{
		ptr[i] = s[i + start];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
/*
int	main(void)
{
	char str[] = "0123456789";
	
	printf("%s\n", str);
	printf("%s", ft_substr(str, 9, 10));
}
*/
