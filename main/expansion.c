/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:55:24 by kbrauer           #+#    #+#             */
/*   Updated: 2024/05/03 13:55:25 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	start_expansion(t_shell *shell)
{
	int		i;
	int		n;
	int		len_str;
	t_list	**ptr;

	i = 0;
	n = 0;
	len_str = 0;
	ptr = shell->lists;
	while (ptr[i])
	{
		while (ptr[i]->content[n])
		{
			if (ptr[i]->content[n] == '$')
			{
				len_str = mal_dollar(shell, &ptr[i]->content[n]);
				ptr[i]->content = replace_dollar(shell, ptr[i]->content, len_str, &ptr[i]->content);//replace $HOME with expanded str
				continue;//n = n + len_str;//increase n by length of $HOME
			}
			n++;
		}
		i++;
	}
	return (0);
}
//create shell->exp_str and return length of dollar str ($HOME = 5)
int	mal_dollar(t_shell *shell, char *str)
{
	int		i;
	char *tmp;

	i = 0;
	str++;
	while (str[i] != ' ' && str[i] != '\n' && str[i] != '\'' && str[i] != '\"' && str[i] != '\0')
		i++;
	tmp = (char *) malloc (sizeof(char) + (i + 1));
	if (!tmp)
		return(-1);
	i = 0;
	while (str[i] != ' ' && str[i] != '\n' && str[i] != '\'' && str[i] != '\"' && str[i] != '\0')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	//if (shell->exp_str)
	//	free (shell->exp_str);
	shell->exp_str = my_getenv(shell, tmp, 1);
	if (!shell->exp_str)
		return (0);
	return (i);
}

char	*replace_dollar(t_shell *shell, char *str, int len, char **ptr)
{
	int		i;
	int		n;
	char *tmp;

	i = 0;
	n = 0;
	while (str[i])
		i++;
	tmp = (char *) malloc (sizeof(char) * (i - len + ft_strlen(shell->exp_str) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i])
	{
		tmp[n] = str[i];
		if (str[i] == '$')
		{
			n = n + replace_dollar_str(shell, &tmp[n]);
			i = i + len;
		}
		i++;
		n++;
	}
	tmp[n] = '\0';
	//free (ptr);
	//printf("replace_dollar *ptr: %s\n", *ptr);
	//printf("replace_dollar tmp: %s\n", tmp);
	// *ptr = tmp;
	return (tmp);
}

int	replace_dollar_str(t_shell *shell, char *tmp)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (shell->exp_str[n])
	{
		//printf("replace_dollar_str tmp[i]: %c\n", tmp[i]);
		//printf("replace_dollar_str shell->exp_str[n]: %c\n", shell->exp_str[n]);
		tmp[i] = shell->exp_str[n];
		i++;
		n++;
	}
	return (n - 1);
}