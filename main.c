/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:44:23 by kbrauer           #+#    #+#             */
/*   Updated: 2024/03/01 15:55:22 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft_bonus/libft.h"


int	main(int argc, char **argv)
{
	char *cmd;
	int i = -1;
	t_shell	shell;
	
	while (1)
	{
		cmd = readline("minishell$ ");
		if (!cmd)
			exit (0);
		
		printf("Input: %s\n", cmd);

		shell.input = ft_split(cmd, ' ');
		while (shell.input && shell.input[++i])
			printf("Token %d: %s\n", i + 1, shell.input[i]);
		
		i = -1;
		while (shell.input[++i])
			free(shell.input[i]);
		free(shell.input);

		if (!strcmp(cmd, "exit"))
			return (free(cmd), 0);
		free(cmd);
		i = -1;
		break ;
	}
	
	
}