/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:54:45 by mvolgger          #+#    #+#             */
/*   Updated: 2024/04/16 10:44:53 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

char	*ft_strdup(t_data *data, const char *s)
{
	size_t	length;
	char	*dest;
	
	if (s == NULL)
		return (NULL);
	length = ft_strlen(s);
	dest = (char *)malloc(length + 1);
	if (dest == NULL)
		free_exit(data, 1);
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
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(t_data *data, char const *s1, char const *s2)
{
	char	*newstr;
	size_t	i;
	size_t	length;

	length = (ft_strlen(s1) + ft_strlen(s2));
	newstr = (char *)malloc(sizeof(char) * (length + 1));
	if (newstr == NULL)
		free_exit(data, 1);
	i = 0;
	while (*s1)
		newstr[i++] = *s1++;
	while (*s2)
		newstr[i++] = *s2++;
	newstr[i] = '\0';
	return (newstr);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dest_ptr;
	const char	*src_ptr;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_ptr = (char *)dest;
	src_ptr = (const char *)src;
	while (n > 0)
	{
		*dest_ptr++ = *src_ptr++;
		n--;
	}
	return (dest);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && (*s1 != '\0' || *s2 != '\0'))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	ret;

	i = 0;
	n = 1;
	ret = 0;
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


