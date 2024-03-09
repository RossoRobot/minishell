/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:44:23 by kbrauer           #+#    #+#             */
/*   Updated: 2024/03/09 14:44:26 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

static int	ft_strcmp(char const *s1, char *s2)
{
	if (*s1 == *s2)
		return (1);
	return (0);
}
//set the type for each token to command/metachar/text
//check 10 bytes so length doesn't matter
int	set_type(t_token *token)
{
	int	i;

	i = 0;
	if (strncmp(token->str, "echo", 10) ||
		strncmp(token->str, "cd", 10) ||
		strncmp(token->str, "pwd", 10) ||
		strncmp(token->str, "export", 10) ||
		strncmp(token->str, "unset", 10) ||
		strncmp(token->str, "env", 10) ||
		strncmp(token->str, "exit", 10))
			token->type = command;
	else if (strncmp(token->str, "|", 10) ||
		strncmp(token->str, ">", 10) ||
		strncmp(token->str, ">>", 10) ||
		strncmp(token->str, "<", 10) ||
		strncmp(token->str, "<<", 10))
			token->type = metachar;
	else
		token->type = text;
	return (0);
}
//malloc 1 more space for pointers to the token structs to add a new token
int	expand_tokens(t_shell shell)
{
	int	i;

	i = 0;
	if (!shell.tokens)
		return 0;
	while (shell.tokens && shell.tokens[i])
		i++;
	shell.tokens = (t_token **) malloc (sizeof(t_token *) * (i + 2));
	if (!shell.tokens)
		return (1);
	shell.tokens[i + 1] = NULL;
	return (0);
}

int	new_token(char *str, t_shell shell)
{
	int	i;
	int	k;
	
	i = 0;
	k = 0;
	expand_tokens(shell);
	while (str[i] >= 33 && str[i] <= 126)
		i++;
	shell.tokens[0]->str = (char *) malloc (sizeof(char) * (i + 1));
	if (!shell.tokens[0]->str)
		return (1);
	i = 0;
	while (str[i] >= 33 && str[i] <= 126)
	{
		shell.tokens[0]->str[i] = str[i];
		i++;
	}
	shell.tokens[0]->str[i] = '\0';
	set_type(shell.tokens[0]);
	


	return (i);
}

int	create_tokens(char *cmd, t_shell shell)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		while (cmd[i] == 9 || cmd[i] == 10 || cmd[i] == 32)
			i++;
		i = i + new_token(&cmd[i], shell);



		
	}


	return (0);
}


int	free_str(t_shell shell)
{
	int	i;

	i = -1;
	while (shell.str[++i])
		free(shell.str[i]);
	free(shell.str);
	return (0);
}
//initiat values for all necessary variables
int	init_values(t_shell shell)
{
	shell.tokens = NULL;
	return (0);
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
		create_tokens(cmd, shell);

		
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
