/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:46:03 by kbrauer           #+#    #+#             */
/*   Updated: 2024/03/01 15:54:45 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>


static void	ft_freeall(char **strarr, int strnb)
{
	int	i;

	i = 0;
	while (i < strnb)
	{
		free(&*strarr[i]);
		i++;
	}
	free(&*strarr);
}

static int	ft_strcmp(char const *s1, char *s2)
{
	if (*s1 == *s2)
		return (1);
	return (0);
}

static int	count_strings(char const *str, char *chr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (ft_strcmp(&str[i], chr))
			i++;
		if (!ft_strcmp(&str[i], chr) && str[i])
		{
			count++;
			while (!ft_strcmp(&str[i], chr) && str[i])
				i++;
		}
	}
	return (count);
}

static char	*new_str(char const *str, char *chr, int *pos)
{
	int		i;
	int		count;
	char	*small_str;

	i = *pos;
	count = 1;
	while (ft_strcmp(&str[i], chr))
		i++;
	while (!ft_strcmp(&str[i], chr) && str[i])
	{
		count++;
		i++;
	}
	*pos = i;
	small_str = (char *) malloc (count * sizeof(char));
	if (!small_str)
		return (0);
	small_str[count - 1] = '\0';
	count -= 1;
	while (--count >= 0)
		small_str[count] = str[--i];
	return (small_str);
}

char	**ft_split(char const *s, char c)
{
	char	**split_arr;
	int		str_nb;
	int		i;
	int		pos;

	str_nb = count_strings(s, &c);
	split_arr = (char **) malloc (sizeof(char *) * (str_nb + 1));
	if (!split_arr)
		return (0);
	pos = 0;
	i = 0;
	while (i < str_nb)
	{
		split_arr[i] = new_str(s, &c, &pos);
		if (split_arr[i] == 0)
		{
			ft_freeall(split_arr, i + 1);
			return (0);
		}
		i++;
	}
	split_arr[i] = 0;
	return (split_arr);
}

/*
#include <stdio.h>
int	main(void)
{
	char	string[] = "|Hier|steht|ein|Haus|";
	char	chr = ' ';
	char	**final_str = ft_split(string, chr);
	int		i = 0;

	while (final_str[i])
	{
		printf("%s\n", final_str[i]);
		i++;
	}
}
*/