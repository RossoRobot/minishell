/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:29:02 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/06 16:29:04 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	count_src;
	unsigned int	count_dst;

	i = 0;
	count_src = 0;
	count_dst = 0;
	while (src[count_src])
		count_src++;
	while (dst[count_dst])
		count_dst++;
	if (size <= count_dst)
		return (count_src + size);
	while (src[i] != 0 && i < (size - count_dst - 1))
	{
		dst[count_dst + i] = src[i];
		i++;
	}
	dst[count_dst + i] = 0;
	return (count_dst + count_src);
}
/*
int main(void)
{
    char source[] = "abcd";
    char destination[] = "123456";
    int  n = 8;

    printf("%s\n", source);
    printf("%s\n", destination);
    printf("%d\n", strlcat(destination, source, n));
    printf("%s\n", destination);
}
*/
