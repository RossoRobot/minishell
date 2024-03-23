/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:37:47 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/14 10:37:49 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;

	i = 0;
	while (s[i])
		i++;
	str = (char *) malloc (sizeof(char) * i + 1);
	if (!str)
		return (0);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}
/*
char	ft_higher(unsigned int n, char c)
{
	char	chr = c;
	chr += n;
	return (chr);
}

int	main(void)
{
	char const string[] = "Hello world!";
	
	printf("%s", ft_strmapi(string, ft_higher));
}
*/
