/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:00:58 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/08 13:01:00 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nb;
	int	flag;

	i = 0;
	nb = 0;
	flag = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == 45)
	{
		flag++;
		i++;
	}
	else if (nptr[i] == 43)
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + nptr[i] - '0';
		i++;
	}
	if (flag % 2 == 0)
		return (nb);
	return (-nb);
}
/*
int	main(void)
{
	char number[] = "  -1234ab567";
	printf("%d\n", atoi(number));
	printf("%d", ft_atoi(number));
}
*/
