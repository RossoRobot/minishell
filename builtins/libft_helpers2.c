/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helpers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:33:40 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/12 13:34:36 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/builtins.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	ret;

	i = 0;
	n = 1;
	ret = 0;
	if (!nptr)
		return (0);
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			n *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		ret = (nptr[i] - '0') + (ret * 10);
		i++;
	}
	return (ret * n);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

int	ft_isalnum(int c)
{
	return (((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		|| (c >= 48 && c <= 57));
}

int	ft_isnum(int c)
{
	return ((c >= 48 && c <= 57));
}
