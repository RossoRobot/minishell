/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:55:07 by kbrauer           #+#    #+#             */
/*   Updated: 2024/05/16 17:31:49 by mvolgger         ###   ########.fr       */
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
	shell->exp_str = NULL;
	shell->env_line = NULL;
	init_values(shell);
	env_duplicate(shell, envp);
	while (1)
	{
		cmd = readline("minishell$ ");
		if (!cmd)
			return (1);
		if (cmd[0] != 0)
			add_history(cmd);
		if (parse(cmd, shell))
			return (1);
		execute(shell);
		free_hname(shell);
		free_parse(shell);
		free(cmd);
	}
}
