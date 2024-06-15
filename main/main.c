/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:55:07 by kbrauer           #+#    #+#             */
/*   Updated: 2024/06/15 12:05:00 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	g_var;

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

static void	handler(int sig, siginfo_t *info, void *ucontext)
{
	g_var = 2;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

//VS code denkt etwas passt da nicht (rot), ist aber alles ok
static void	recieve_signal(t_shell *shell, struct sigaction *action_c)
{
	action_c->sa_sigaction = &handler;
	action_c->sa_flags = SA_SIGINFO;
	sigemptyset(&action_c->sa_mask);
	if (sigaction(SIGINT, action_c, NULL) == -1)
		ft_exit(shell, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char				*cmd;
	t_shell				*shell;
	struct sigaction	action_c;

	shell = (t_shell *) malloc (sizeof(t_shell));
	if (!shell)
		return (0);
	first_init(shell);
	init_values(shell);
	env_duplicate(shell, envp);
	recieve_signal(shell, &action_c);
	while (1)
	{
		cmd = readline("minishell$ ");
		if (g_var == 2)
			set_return_value(shell, 2);
		g_var = 0;
		shell->h_lines++;
		if (!cmd)
			free_exit(shell, 1);
		if (press_enter_only(cmd))
			continue ;
		if (process(shell, cmd))
			return (1);
		free(cmd);
	}
}
