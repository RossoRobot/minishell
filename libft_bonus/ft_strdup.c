/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:56:57 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/08 15:57:01 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i])
		i++;
	ptr = (char *) malloc (i * sizeof(char) + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = s[i];
	return (ptr);
}
/*
int	main(void)
{
	const char	str[] = "Please copy me";
	
	printf("%s\n", strdup(str));
	printf("%s", ft_strdup(str));
}
*/
