/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:55:07 by kbrauer           #+#    #+#             */
/*   Updated: 2024/04/23 19:43:13 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"


int	main(int argc, char **argv, char **envp)
{
	char 	*cmd;
	t_shell	*shell;

	shell = (t_shell*) malloc (sizeof(t_shell));
	if (!shell)
		return (0);
	init_values(shell);
	shell->env_line = NULL;
	env_duplicate(shell, envp);
	while (1)
	{
		cmd = readline("minishell$ ");
		if (!cmd)
			return (1);
		parse(cmd, shell);
		execute(shell);
		free_parse(shell);
		//if (!ft_strncmp(cmd, "exit", 10))
		//	return (free_exit(shell, 0), free(cmd), 0);
		free(cmd);
	}
}
