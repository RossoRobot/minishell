/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:55:07 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/06 17:27:13 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

// static void	print_hnames(t_shell *shell)
// {
// 	t_hname	*ptr;

// 	ptr = shell->hname;
// 	printf("HNAMES:\n");
// 	while (ptr)
// 	{
// 		printf("%s\n", ptr->content);
// 		ptr = ptr->next;
// 	}
// }

static int	process(t_shell *shell, char *cmd)
{
	add_history(cmd);
	if (parse(cmd, shell))
		return (0);
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
	char				*cmd;
	t_shell				*shell;

	shell = (t_shell *) malloc (sizeof(t_shell));
	test_malloc(shell);
	first_init(shell, argc, argv);
	init_values(shell);
	env_duplicate(shell, envp);
	while (1)
	{
		recieve_signal(shell, 0, 0);
		cmd = readline("minishell$ ");
		recieve_signal(shell, 2, 1);
		if (g_var == 2)
			set_return_value(shell, 130);
		g_var = 0;
		shell->h_lines++;
		if (!cmd)
			free_exit(shell, 1408);
		if (press_enter_only(cmd))
			continue ;
		if (process(shell, cmd))
			return (1);
		free(cmd);
	}
}
