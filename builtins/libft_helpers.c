/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:54:45 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/25 11:25:09 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/builtins.h"

char	*ft_strchr(const char *s, int c)
{
	char	c1;

	c1 = (unsigned char)c;
	while (*s)
	{
		if (*s == c1)
			return ((char *)s);
		s++;
	}
	if (c1 == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_strdup(t_shell *data, const char *s)
{
	size_t	length;
	char	*dest;

	if (s == NULL)
		return (NULL);
	length = ft_strlen(s);
	dest = (char *)malloc(length + 1);
	if (dest == NULL)
		free_exit(data, 138);
	ft_strlcpy(dest, s, length + 1);
	return (dest);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(src);
	if (size != 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (j);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(t_shell *data, char const *s1, char const *s2)
{
	char	*newstr;
	size_t	i;
	size_t	length;

	length = (ft_strlen(s1) + ft_strlen(s2));
	newstr = (char *)malloc(sizeof(char) * (length + 1));
	if (newstr == NULL)
		free_exit(data, 138);
	i = 0;
	while (*s1)
		newstr[i++] = *s1++;
	while (*s2)
		newstr[i++] = *s2++;
	newstr[i] = '\0';
	return (newstr);
}
