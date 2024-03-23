/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:29:01 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/05 10:29:03 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	unsigned char chr = '0';
	printf("%d\n",ft_isdigit(chr));
	printf("%d",isdigit(chr));
	return(0);	
}
*/
