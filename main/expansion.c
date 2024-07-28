/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:55:24 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/28 16:07:13 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	expansion(t_shell *shell)
{
	int		i;
	int		n;
	int		len_str;
	int		flag;
	t_list	*ptr;

	if (!set_data(&i, NULL, &flag, shell))
		return (1);
	ptr = shell->lists[i];
	while (ptr)
	{
		n = 0;
		while (ptr->content && ptr->content[n])
		{
			len_str = 0;
			set_flag(&ptr->content[n], &flag);
			if (ptr->content[n] == '$' && flag != 1 && ptr->type != here_del)
				flag = expand_str(shell, &n, ptr);
			n++;
		}
		ptr = ptr->next;
		if (!ptr)
			ptr = shell->lists[++i];
	}
	return (0);
}

// create shell->exp_str and return length of dollar str ($HOME = 5)
int	mal_dollar(t_shell *shell, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	str++;
	while (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'
		|| str[i] == '!')
		i++;
	tmp = (char *)malloc(sizeof(char) + (i + 1));
	if (!tmp)
		return (-1);
	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'
		|| str[i] == '!')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	if (shell->exp_str)
		free_to_null(&shell->exp_str);
	set_exp_str(shell, tmp);
	if (!shell->exp_str)
		free(tmp);
	return (i);
}

char	*replace_dollar(t_shell *shell, char *str, int len)
{
	int		i;
	int		n;
	int		flag;
	char	*tmp;

	set_data(&i, &n, &flag, shell);
	while (str[i])
		i++;
	tmp = malloc(sizeof(char) * (i - len + ft_strlen(shell->exp_str) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i])
	{
		tmp[n] = str[i];
		set_flag(&str[i], &flag);
		if (str[i] == '$' && (flag == 0 || flag == 2))
			n = replace_dollar_helper(&n, &i, &flag, len)
				+ replace_dollar_str(shell, &tmp[n]);
		i++;
		n++;
	}
	tmp[n] = '\0';
	free(str);
	return (tmp);
}

int	replace_dollar_str(t_shell *shell, char *tmp)
{
	int	i;
	int	n;
	int	c;

	i = 0;
	n = 0;
	c = 0;
	if (!shell->exp_str)
		return (-1);
	while (shell->exp_str[n])
	{
		tmp[i] = shell->exp_str[n];
		i++;
		n++;
	}
	return (n - 1);
}
