/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:26:23 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/28 20:04:37 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	set_here_del_type(t_shell *shell)
{
	t_list	*ptr;
	int		i;

	i = 0;
	if (!shell->lists)
		return ;
	ptr = shell->lists[i];
	while (ptr)
	{
		if (ptr->type == he_doc && ptr->next)
			ptr->next->type = here_del;
		ptr = ptr->next;
		if (!ptr)
			ptr = shell->lists[++i];
	}
	ptr = NULL;
}

int	start_w_red(char *str)
{
	int		i;
	int		n;

	i = 0;
	while (str[i] == ' ')
		i++;
	n = i;
	while (str[n] == '<')
		n++;
	if (n == i + 2 && str[n] != '<' && str[n] != '>')
		return (0);
	n = 0;
	while (str[i + n] == '>')
	{
		n++;
		if ((n == 1 || n == 2) && str[i + n] == 0)
			return (1);
		return (1);
	}
	n = 0;
	while (str[i + n] == '<')
	{
		n++;
		if ((n >= 1 && n <= 3) && str[i + n] == 0)
			return (1);
		return (1);
	}
	return (0);
}

int	red_del(t_shell *shell, t_list *ptr)
{
	char	*tmp;

	tmp = ptr->next->content;
	if (ptr->next->content[0] == '<' || ptr->next->content[0] == '>')
	{
		ft_putstr_fd("minishell: syntax error near \
unexpected token `", 2);
		if (ptr->next->content[0] == '<')
			write(2, "<", 1);
		if (ptr->next->content[0] == '>')
			write(2, ">", 1);
		if (ptr->next->content[1] == '<' && ptr->next->content[1] == tmp[0])
			write(2, "<", 1);
		if (ptr->next->content[1] == '>')
			write(2, ">", 1);
		if (ptr->next->content[1] && ptr->next->content[2] == '<'
				&& ptr->next->content[2] == tmp[0]
				&& ptr->next->content[1] == '<')
			write(2, "<", 1);
		write(2, "'\n", 2);
		return (set_return_value(shell, 2), 2);
	}
	return (0);
}

int	correct_red(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len <= 1)
		return (1);
	if (len == 2)
	{
		if ((str[0] == '<' || str[0] == '>') && (str[1] != ' '
				&& str[1] != '<' && str[1] != '>'))
			return (0);
	}
	if (len >= 3)
	{
		if ((str[1] != '<' && str[1] != '>')
				&& str[2] != '<' && str[2] != '>')
			return (0);
		if ((str[0] == '<' && str[0] == str[1]) && str[2] != '<'
				&& str[2] != '>' && str[2] != ' ')
			return (0);
		if ((str[0] == '>' && str[0] == str[1]) && str[2] != '<'
				&& str[2] != '>' && str[2] != ' ')
			return (0);
	}
	return (1);
}
