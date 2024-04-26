/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:39:31 by kbrauer           #+#    #+#             */
/*   Updated: 2024/04/19 14:36:31 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

t_list	*ft_lstnew(char *str, int *k, t_shell *shell)
{
	t_list	*start;
	int		i;
	int		flag;
	int		len;
	int		n;

	if (!str)
		return (NULL);
	start = (t_list *) malloc (sizeof(t_list));
	if (!start)
		return (NULL);
	flag = 0;
	//while a delimiter
	str = while_del(str);
	//check if str starts with a "-sign or '-sign
	set_flag(&str[0], &flag);
	//while NOT a delimiter, count str length
	i = while_not_del(str, flag, shell, k);
	start->content = (char *) malloc (sizeof(char) * (i + 1));
	if (!start->content)
		return (NULL);
	//*k = i;
	i = 0;
	len = 0;
	n = 0;
	while (str[i] && (check_del(str[i], flag) == 0) && str[i] != '\n')
	{
		if (str[i] == '$' && str[i + 1] != '\n' && str[i + 1] != '\0')
		{
			expand(shell, &str[i + 1], &len);
			while (shell->exp_str && shell->exp_str[n] != '\0')
			{
				start->content[i + n] = shell->exp_str[n];
				n++;
			}
			if (shell->exp_str)
				free(shell->exp_str);
			i = i + len;
			if (str[i] && (check_del(str[i], flag) == 0) && str[i] != '\n')
				break ;
		}
		start->content[i + n] = str[i];
		i++;
		set_flag(&str[i], &flag);
	}
	start->content[i + n] = '\0';
	start->type = text_a;
	start->next = NULL;
	return (start);
}

void	ft_lstadd_back(t_list *lst, t_list *new)
{
	t_list	*ptr;

	ptr = lst;
	if (lst)
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
		ptr = NULL;
	}
	else
		lst = new;
}

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (i < (n - 1) && s1[i] == s2[i] && s1[i] != 0)
// 		i++;
// 	if (n == 0)
// 		return (0);
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

//check if chr equals one of the DEL (delimiters)
int	check_del(char	chr, int flag)
{
	int	i;

	i = 0;
	if (flag)
		return (0);
	while (DEL[i])
	{
		if (chr == DEL[i])
			return (1);
		i++;
	}
	return (0);
}