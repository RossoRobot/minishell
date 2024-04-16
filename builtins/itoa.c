/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:10:47 by mvolgger          #+#    #+#             */
/*   Updated: 2024/04/10 16:10:58 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_getdigits(int number)
{
	int	digits;

	digits = 0;
	while (number != 0)
	{
		number /= 10;
		digits++;
	}
	return (digits);
}

static	int	ft_isnegative(int number)
{
	if (number < 0)
		return (1);
	else
		return (0);
}

static	char	*ft_cpytostr(int n, char *str, int index, int isnegative)
{
	str[index] = '\0';
	index--;
	if (n == -2147483648)
	{
		str[index] = '8';
		n /= 10;
		index--;
	}
	if (isnegative == 1)
		n *= -1;
	while (n != 0)
	{
		str[index--] = (n % 10) + '0';
		n /= 10;
	}
	if (isnegative == 1)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int		digits;
	int		isnegative;
	int		index;
	char	*str;

	digits = ft_getdigits(n);
	isnegative = ft_isnegative(n);
	index = digits + isnegative;
	if (n == 0)
	{
		str = (char *)malloc(sizeof(char) * 2);
		if (!str)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (digits + isnegative + 1));
	if (str == NULL)
		return (NULL);
	ft_cpytostr(n, str, index, isnegative);
	return (str);
}