/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:49:04 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/14 13:49:06 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void	ft_higher(unsigned int n, char *c)
{
	*c += n;
}

int	main(void)
{
	char	string[] = "Hello world!";

	printf("%s\n", string);
	ft_striteri(string, ft_higher);
	printf("%s", string);
}
*/
