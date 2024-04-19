/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:59:07 by kbrauer           #+#    #+#             */
/*   Updated: 2024/04/19 15:40:36 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	mal_list(t_shell *shell)
{
	shell->lists = (t_list **) malloc (sizeof(t_list *) * (shell->n_pipes + 2));
	if (!shell->lists)
		return ;
	shell->lists[shell->n_pipes + 1] = NULL;
}

void	create_tokens(char *input, t_shell *shell)
{
	int		i;
	int		k;
	int		flag;
	char	*str;
	t_list	*tmp;
	
	i = 0;
	k = 0;
	str = input;
	//malloc pointers for lists
	mal_list(shell);
	//create list, store beginning (address) of first command
	while (shell->n_pipes + 1)
	{
		//ignore tab/space/newline at beginning of string
		str = skip_gap(str);
		shell->lists[i] = ft_lstnew(str, &k);
		while(*str)
		{
			flag = 0;
			while (k-- != 0)
				str++;
			//go over first command
			//str = skip_argument(str);
			
			//go over tab/space/newline
			str = skip_gap(str);
			while (*str == '|')
			{
				flag = 1;
				str++;
			}
			if (flag)
				break;
			tmp = ft_lstnew(str, &k);
			ft_lstadd_back(shell->lists[i], tmp);
		}
		i++;
		shell->n_pipes--;
	}
}


void print_tokens(t_shell *shell)
{
	t_list	*ptr;
	int		i;

	i = 0;
	while (shell->lists[i])
	{
		ptr = shell->lists[i];
		while (ptr)
		{
			printf("%s\n", ptr->content);
			printf("%d\n", ptr->type);
			ptr = ptr->next;
		}
		i++;
	}
	ptr = NULL;
}

int	check_input(char *str, t_shell *shell)
{
	int	i;
	int	flag1;
	int	flag2;

	i = 0;
	flag1 = 0;
	flag2 = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			while (str[i] == '|')
				i++;
			shell->n_pipes++;
		}
		if (str[i] == '\"')
			flag1++;
		if (str[i] == '\'')
			flag2++;
		i++;
	}
	if (flag1 % 2 || flag2 % 2)
		return (printf("Error with quotation!\n"), 1);
	return (0);
}

int	init_values(t_shell *shell)
{
	shell->env_arr = NULL;
	shell->env_line = NULL;
	shell->lists = NULL;
	shell->n_pipes = 0;
	return (0);
}

int parse(char *cmd, t_shell *shell)
{
    init_values(shell);
    check_input(cmd, shell);
	//integrate extensions
	create_tokens(cmd, shell);
	define_type(shell);
	print_tokens(shell);
	free_all(shell);
    return (0);
}
