/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:26:04 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/08 11:26:07 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_increase(unsigned int *i, unsigned int *j)
{
	++*i;
	++*j;
}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	start_pos;

	i = 0;
	j = 0;
	while (str[i] != 0 && i < len)
	{
		if (str[i] == to_find[j])
		{
			start_pos = i;
			while (str[i] == to_find[j] && to_find[j] && i < len)
				ft_increase(&i, &j);
			if (to_find[j] == 0)
				return ((char *)&str[start_pos]);
			j = 0;
			i = start_pos;
		}
		i++;
	}
	if (to_find[0] == 0)
		return ((char *)&str[0]);
	return (0);
}
/*
int main(void)
{
    const char first_string[] = "aaabcabcd";
    const char to_find[] = "aabc";
    size_t	count = 9;

   printf("%s\n", first_string);
   //printf("%s\n", strnstr(first_string, to_find, 7));
   printf("%s\n", strnstr("aaabcabcd", "aabc", count));
   printf("%s", ft_strnstr(first_string, to_find, count));
}
*/
