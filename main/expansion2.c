/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:58:37 by kbrauer           #+#    #+#             */
/*   Updated: 2024/06/14 12:58:39 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	expand_str(t_shell *shell, int *n, t_list *ptr)
{
	int	len_str;

	len_str = mal_dollar(shell, &ptr->content[*n]);
	ptr->content = replace_dollar(shell, ptr->content, len_str);
	*n = -1;
	return (0);
}

int	replace_dollar_helper(int *n, int *i, int *flag, int len)
{
	*i = *i + len;
	*flag = 3;
	return (*n);
}

int	check_shlvl(char *str)
{
	return (ft_strncmp(str, "./minishell", 11));
}
