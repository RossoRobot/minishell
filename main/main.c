/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:55:07 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/21 18:23:25 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

static int	process(t_shell *shell, char *cmd)
{
	shell->hd_cc_flag = 0;
	add_history(cmd);
	if (parse(cmd, shell))
		return (1);
	if (shell->hd_cc_flag == 1)
	{
		set_return_value(shell, 130);
		free_hname(shell);
		free_parse(shell);
		return (0);
	}
	execute(shell);
	free_hname(shell);
	free_parse(shell);
	return (0);
}

static int	press_enter_only(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == 0)
		return (free(cmd), 1);
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	if (!cmd[i])
		return (free(cmd), 1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell				*shell;

	shell = (t_shell *) malloc (sizeof(t_shell));
	test_malloc(shell);
	first_init(shell, argc, argv);
	init_values(shell);
	env_duplicate(shell, envp);
	while (1)
	{
		recieve_signal(shell, 0, 0, "0");
		shell->cmd = readline("minishell$ ");
		recieve_signal(shell, 2, 1, shell->cmd);
		if (g_var == 2)
			set_return_value(shell, 130);
		g_var = 0;
		shell->h_lines++;
		if (!shell->cmd)
			free_exit(shell, 1408);
		if (press_enter_only(shell->cmd))
			continue ;
		if (process(shell, shell->cmd))
			continue;
		free(shell->cmd);
	}
}
