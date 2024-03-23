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
	char	*str;
	t_list	*tmp;
	
	i = 0;
	str = input;
	mal_list(shell);
	//ignore tab/space/newline at beginning of string
	while (*str == 9 || *str == 10 || *str == 32)
			str++;
	//create list, store beginning (address) of first command
	while (shell->n_pipes + 1)
	{
		shell->lists[i] = ft_lstnew(str);
		while(*str)
		{
			//go over first command
			while ((*str != 9 && *str != 10 && *str != 32) && *str)
				str++;
			//go over tab/space/newline
			while ((*str == 9 || *str == 10 || *str == 32) && *str)
				str++;
			if (*str == '|')
				break;

			tmp = ft_lstnew(str);
			ft_lstadd_back(shell->tokens, tmp);
			
		}
		i++;
		shell->n_pipes--;
	}
	//printf("lst1.1: %s\n", shell->lists[0]->content);
	//printf("lst1.2: %s\n", shell->lists[0]->next->content);
	//printf("lst2.1: %s\n", shell->lists[1]->content);
	//printf("lst2.2: %s\n", shell->lists[1]->next->content);
}


void print_tokens(t_shell *shell)
{
	t_list	**ptr;
	int		i;

	i = 0;
	ptr = shell->lists;
	printf("%d", shell->lists[i]->type);
	printf("print: %s\n", ptr[i]->content);
	while (i < shell->n_pipes + 1)
	{
		while (ptr[i])
		{
			printf("%s\n", ptr[i]->content);
			ptr[i] = ptr[i]->next;
		}
		i++;
	}
}

int	check_input(char *str, t_shell *shell)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			shell->n_pipes++;
		i++;
	}

	return (0);
}

int	init_values(t_shell *shell)
{
	shell->tokens = NULL;
	shell->lists = NULL;
	shell->n_pipes = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	char *cmd;
	int i = -1;
	t_shell	shell;
	
	init_values(&shell);
	while (1)
	{
		cmd = readline("minishell$ ");
		if (!cmd)
			exit (1);
		check_input(cmd, &shell);
		create_tokens(cmd, &shell);
		//print_tokens(&shell);
		free_all(&shell);
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
