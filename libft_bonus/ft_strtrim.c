/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:58:42 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/13 14:58:44 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcmp(char const *s1, char const *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (*s1 == s2[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (s1[i] == 0)
		return (ft_substr(s1, 0, 0));
	while (s1[i])
	{
		while (ft_strcmp(&s1[i], set) && i == k && s1[i])
		{
			k++;
			i++;
		}
		if (s1[i] == 0)
			return (ft_substr(s1, 0, 0));
		i++;
	}
	i--;
	while (ft_strcmp(&s1[i], set))
		i--;
	return (ft_substr(s1, k, ++i - k));
}
/*
#include <stdio.h>
int	main(void)
{
	char string[] = "   xxx   xxx";
	char set[] = " x";
	
	printf("%s", ft_strtrim(string, set));
}
*/