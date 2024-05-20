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


static int	process(t_shell *shell, char *cmd)
{
	add_history(cmd);
	if (parse(cmd, shell))
		return (1);
	execute(shell);
	free_hname(shell);
	free_parse(shell);
	return (0);
}

static int	press_enter_only(char *cmd)
{
	if (cmd[0] == 0)
		return (free(cmd), 1);
	return (0);	
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	if (sig == 2)
	{
		printf("CTR-C pressed - sigvalue: %d\n", sig);
		exit(1);
	}
	if (sig >= 0 && sig <= 6)
		printf("CTR-D pressed - sigvalue: %d\n", sig);
}
//VS code denkt etwas passt da nicht (rot), ist aber alles ok
void	recieve_signal(struct sigaction *action)
{
	action->sa_sigaction = &handler;
	action->sa_flags = SA_SIGINFO;
	sigemptyset(&action->sa_mask);
	if (sigaction(SIGINT, action, NULL) == -1)
		exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	char 				*cmd;
	t_shell				*shell;
	struct sigaction	action;

	recieve_signal(&action);
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
		if (press_enter_only(cmd))
			continue;
		if (process(shell, cmd))
			return (1);
		free(cmd);
	}
}
