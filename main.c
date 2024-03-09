/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:55:07 by kbrauer           #+#    #+#             */
/*   Updated: 2024/03/09 19:12:55 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>


void	create_tokens(char *input, t_shell shell)
{
	int		i;
	char	*str;
	t_list	*lst;
	t_list	*tmp;
	
	i = 0;
	str = input;
	//ignore tab/space/newline at beginning of string
	while (*str == 9 || *str == 10 || *str == 32)
			str++;
	//create list, store beginning (address) of first command
	shell.tokens = ft_lstnew(str);
	printf("lst1: %s\n", shell.tokens->content);
	printf("lst1: %i\n", shell.tokens->type);
	while(*str)
	{
		//go over first command
		while ((*str != 9 && *str != 10 && *str != 32) && *str)
			str++;
		//go over tab/space/newline
		while ((*str == 9 || *str == 10 || *str == 32) && *str)
			str++;
		tmp = ft_lstnew(str);
		ft_lstadd_back(shell.tokens, tmp);
		
		printf("lst2: %s\n", shell.tokens->next->content);
		printf("lst2: %i\n", shell.tokens->next->type);
	}
	
	
}

int	check_input(char *str, t_shell shell)
{
	int	i;

	i = 0;
	while (str[i])
		i++;

	return (0);
}

int	init_values(t_shell shell)
{
	shell.tokens = NULL;
	return (0);
}

void print_tokens(t_shell shell)
{
	t_list	*ptr;

	ptr = shell.tokens;
	printf("print\n");
	while (ptr)
	{
		printf("%s\n", ptr->content);
		printf("print2\n");
		ptr = ptr->next;
	}
}

int	main(int argc, char **argv)
{
	char *cmd;
	int i = -1;
	t_shell	shell;
	
	init_values(shell);
	while (1)
	{
		cmd = readline("minishell$ ");
		if (!cmd)
			exit (1);
		//check_input(cmd, shell);
		create_tokens(cmd, shell);
		printf("MAIN\n");
		//print_tokens(shell);
		
		// printf("User input: %s\n", cmd);

		// shell.str = ft_split(cmd, ' ');
		// while (shell.str && shell.str[++i])
		// 	printf("Token %d: %s\n", i + 1, shell.str[i]);
		// free_str(shell);
		

		if (!ft_strncmp(cmd, "exit", 10))
			return (free(cmd), 0);
		free(cmd);
		i = -1;
	}
	
	
}
