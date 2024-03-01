/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:11:58 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/14 10:11:59 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_posnbr(int nb, int fd)
{
	char	new_nb;

	if (nb < 10)
	{
		new_nb = nb + 48;
		write(fd, &new_nb, 1);
	}
	else
	{
		ft_posnbr(nb / 10, fd);
		new_nb = (nb % 10) + 48;
		write(fd, &new_nb, 1);
	}
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		nb = (nb / 10) * -1;
		write(fd, "-", 1);
		ft_posnbr(nb, fd);
		write(fd, "8", 1);
	}
	else if (nb < 0)
	{
		nb = -nb;
		write(fd, "-", 1);
		ft_posnbr(nb, fd);
	}
	else
		ft_posnbr(nb, fd);
}
/*
int	main(void)
{
	ft_putnbr_fd(-2147483648, 1);
	ft_putnbr_fd(-123, 1);
	ft_putnbr_fd(0, 1);
	ft_putnbr_fd(123, 1);
	ft_putnbr_fd(2147483647, 1);
}
*/
