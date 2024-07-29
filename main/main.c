/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:55:07 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/29 19:36:04 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

static int	zwischenparser3000(t_shell *shell)
{
	int		i;
	t_list	*temp;

	i = 0;
	while (shell->lists[i])
	{
		temp = shell->lists[i];
		while (temp->next)
			temp = temp->next;
		if (temp->type == 4 || temp->type == 5 || temp->type == 7)
		{
			if (temp->type == 4)
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
			else
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
			set_return_value(shell, 2);
			free_hname(shell);
			free_parse(shell);
			return (1);
		}
		i++;
	}
	return (0);
}

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
	if (zwischenparser3000(shell))
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

static void	controld_exit(t_shell *data, int last_return_value)
{
	t_env	*temp;

	while (data->env_line != NULL)
	{
		temp = data->env_line;
		if (temp->key_value)
		{
			if (temp->key_value->key)
				free(temp->key_value->key);
			if (temp->key_value->value)
				free(temp->key_value->value);
			free(temp->key_value);
		}
		data->env_line = data->env_line->next;
		if (temp)
			free(temp);
	}
	free_arr(data->env_arr);
	free(data);
	ft_putstr_fd("exit\n", 2);
	exit(last_return_value);
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
			controld_exit(shell, get_last_return_value(shell));
		if (press_enter_only(shell->cmd))
			continue ;
		if (process(shell, shell->cmd))
			continue ;
		free(shell->cmd);
	}
}
