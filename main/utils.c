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

	if (!str)
		free_exit(shell, 1);
	start = (t_list *) malloc (sizeof(t_list));
	if (!start)
		free_exit(shell, 1);
	flag = 0;
	str = while_del(shell, str);
	set_flag(&str[0], &flag);
	i = while_not_del(str, &flag, shell, k);
	start->content = (char *) malloc (sizeof(char) * (i + 1));
	if (!start->content)
		free_exit(shell, 1);
	i = 0;
	set_flag(&str[0], &flag);
	while (str[i] && (chk_del(shell, &str[i], &flag, i) == 0) && str[i] != '\n')
	{
		start->content[i] = str[i];
		i++;
		set_flag(&str[i], &flag);
	}
	return (start->content[i] = '\0', start->next = NULL, start);
}

//check if chr equals one of the DEL (delimiters)
int	chk_del(t_shell *shell, char *chr, int *flag, int pos)
{
	int		i;

	i = 0;
	if (*flag)
		return (0);
	if (pos > 0 && (*chr == '<' | *chr == '>'))
	{
		if (shell->del_flag == 1)
			return (0);
		return (1);
	}
	if (pos == 0 && (*chr == '<' | *chr == '>'))
	{
		shell->del_flag = 1;
		return (0);
	}
	while (DEL[i])
	{
		if (*chr == DEL[i])
			return (shell->del_flag = 0, 1);
		i++;
	}
	if (shell->del_flag == 1 && *chr != '<' && *chr != '>')
		return (printf("chk_del"), shell->del_flag = 0, 1);
	return (0);
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

t_hname	*ft_lstnew_hdoc(t_shell *shell, void *content)
{
	t_hname	*start;
	t_shell	*ptr;

	ptr = shell;
	start = (t_hname *) malloc (sizeof(t_hname));
	if (!start)
		return (NULL);
	start->content = content;
	start->next = NULL;
	return (start);
}

void	ft_lstadd_back_hdoc(t_hname *lst, t_hname *new)
{
	t_hname	*ptr;

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
