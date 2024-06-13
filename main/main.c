/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:55:07 by kbrauer           #+#    #+#             */
/*   Updated: 2024/05/28 17:08:57 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"


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
	if (cmd[0] == 0)
		return (free(cmd), 1);
	return (0);	
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	printf("\nminishell$ ");
	/*
	if (sig == 2)
	{
		printf("handler CTRL-C pressed - sigvalue: %d\n", sig);

	}
	*/
	//printf("handler CTRL-D pressed - sigvalue: %d\n", sig);
}
//VS code denkt etwas passt da nicht (rot), ist aber alles ok
void	recieve_signal(t_shell *shell, struct sigaction *action_c, struct sigaction *action_d)
{
	action_c->sa_sigaction = &handler;
	action_c->sa_flags = SA_SIGINFO;
	sigemptyset(&action_c->sa_mask);
	if (sigaction(SIGINT, action_c, NULL) == -1)
		ft_exit(shell, NULL);
	
	action_d->sa_sigaction = &handler;
	action_d->sa_flags = SA_SIGINFO;
	sigemptyset(&action_d->sa_mask);
	if (sigaction(SIGQUIT, action_d, NULL) == -1)
		ft_exit(shell, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char 				*cmd;
	t_shell				*shell;
	struct sigaction	action_c;
	struct sigaction	action_d;

	shell = (t_shell*) malloc (sizeof(t_shell));
	if (!shell)
		return (0);
	shell->exp_str = NULL;
	shell->env_line = NULL;
	shell->hname = NULL;
	shell->h_lines = 0;
	init_values(shell);
	env_duplicate(shell, envp);
	recieve_signal(shell, &action_c, &action_d);
	while (1)
	{
		cmd = readline("minishell$ ");
		shell->h_lines++;
		if (!cmd)
			free_exit(shell, 1);
		if (press_enter_only(cmd))
			continue;
		if (process(shell, cmd))
			return (1);
		free(cmd);
	}
}
