/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:37:34 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/08 14:37:36 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb * size != 0)
		if ((nmemb * size) / size != nmemb)
			return (0);
	ptr = (void *) malloc (nmemb * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
/*
int	main(void)
{
	int	i = 0;
	int	nmemb = 30;
	int	size = 1;
	char	*ar;
	char	*br;

	ar = calloc(nmemb, size);
	br = ft_calloc(nmemb, size);
	
    write(1, ar, 30);
    write(1, "\n", 1);
    write(1, br, 30);
	
	while (i < nmemb+1)
	{
		printf("%p", ar[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < nmemb+1)
	{
		printf("%p", br[i]);
		i++;
	}
	
}
*/
