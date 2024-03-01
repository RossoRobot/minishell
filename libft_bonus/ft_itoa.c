/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:45:06 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/13 16:45:08 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_fill_str(char *s, int n, int size)
{
	int	i;
	int	nb;

	i = size;
	if (n < 0)
		nb = -n;
	else
		nb = n;
	while (i > 0)
	{
		s[i] = nb % 10 + 48;
		nb = nb / 10;
		i--;
	}
	if (n >= 0)
		s[i] = nb % 10 + 48;
	else if (n < 0)
		s[i] = '-';
}

char	*ft_itoa(int n)
{
	int		i;
	int		nbr;
	char	*str;

	nbr = n;
	i = 0;
	if (nbr <= 0)
		i = 1;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	str = (char *)malloc (i * sizeof(char) + 1);
	if (!str)
		return (NULL);
	str[i] = '\0';
	i--;
	nbr = n;
	if (n == -2147483648)
		nbr = -2147483647;
	ft_fill_str(str, nbr, i);
	if (n == -2147483648)
		str[10] = '8';
	return (str);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(-123));
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(123));
	printf("%s", ft_itoa(2147483647));
}
*/
