/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:48:40 by kbrauer           #+#    #+#             */
/*   Updated: 2023/09/08 18:48:43 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			i;
	int			k;
	char		*new_str;

	i = 0;
	k = 0;
	while (s1[i])
		i++;
	while (s2[k])
		k++;
	new_str = (char *)malloc((i + k) * sizeof(char) + 1);
	if (!new_str)
		return (0);
	i = -1;
	k = -1;
	while (s1[++i])
		new_str[i] = s1[i];
	while (s2[++k])
		new_str[i + k] = s2[k];
	new_str[i + k] = '\0';
	return (new_str);
}
/*
int	main(void)
{
	char	str1[] = "This is ju";
	char	str2[] = "st one string";
	
	printf("%s", ft_strjoin(str1, str2));
}
*/
