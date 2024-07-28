/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:38:28 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/28 16:15:34 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

static int	ft_countwords(char *s1, char c)
{
	int	i;
	int	words;

	if (!s1)
		return (0);
	i = 0;
	words = 0;
	while (s1 && s1[i] && s1[i] == c)
		i++;
	while (s1[i] != '\0')
	{
		while (s1[i] == c && s1[i] != '\0')
			i++;
		if (s1[i] != c && s1[i] != '\0')
		{
			words++;
			while (s1[i] != c && s1[i] != '\0')
				i++;
		}
	}
	return (words);
}

static void	ft_strcpy(char *src, char *dest, char c, int start)
{
	int	i;

	i = 0;
	while (src[start] != '\0' && src[start] == c)
		start++;
	while (src[start + i] != '\0' && src[start + i] != c)
	{
		dest[i] = src[start + i];
		i++;
	}
	dest[i] = '\0';
}

static int	ft_strlength(char *s1, char c, int *pos)
{
	int	i;

	i = 0;
	while (s1[*pos] == c)
		(*pos)++;
	while (s1[*pos + i] != c && s1[*pos + i] != '\0')
		i++;
	return (i);
}

static char	*ft_substralloc(char *s1, char c, int *pos)
{
	int		start;
	char	*substr;
	int		length;

	length = ft_strlength((char *)s1, c, pos);
	start = *pos;
	substr = NULL;
	while (s1[*pos] != '\0')
	{
		if (s1[*pos] == c)
		{
			substr = (char *)malloc(sizeof(char) * (length + 1));
			if (substr == NULL)
				return (NULL);
			break ;
		}
		(*pos)++;
	}
	if (substr == NULL)
		substr = (char *)malloc(sizeof(char) * (length + 1));
	if (substr == NULL)
		return (NULL);
	ft_strcpy(s1, substr, c, start);
	return (substr);
}

char	**ft_split(const char *s1, char c)
{
	char	**strs;
	int		words;
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	words = ft_countwords((char *)s1, c);
	strs = (char **)malloc(sizeof(char *) * (words + 1));
	if (strs == NULL)
		return (NULL);
	strs[words] = NULL;
	while (i < words)
	{
		strs[i] = ft_substralloc((char *)s1, c, &pos);
		if (strs[i] == NULL)
		{
			while (i >= 0)
				free(strs[i--]);
			free(strs);
			return (NULL);
		}
		i++;
	}
	return (strs);
}
