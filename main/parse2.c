/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:58:25 by kbrauer           #+#    #+#             */
/*   Updated: 2024/06/14 17:58:27 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

t_shell	*set_data_return_shell(t_shell *shell, int *i, int *k, int *pipes)
{
	*i = 0;
	*k = 0;
	*pipes = shell->n_pipes;
	return (shell);
}

int	while_pipe(char *input, int *flag)
{
	int	i;

	i = 0;
	while (*input == '|')
	{
		*flag = 1;
		input++;
		i++;
	}
	return (i);
}

void	increase_i_decrease_pipes(int *i, int *pipes)
{
	*i += 1;
	*pipes -= 1;
}

int	set_input(char **input)
{
	*input = skip_gap(*input);
	return (0);
}

int	start_w_pipe(t_shell *shell, char *str)
{
	int	i;
	t_shell	*dummy;

	dummy = shell;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (str[i] == ';')
	{
		printf("minishell: syntax error near unexpected token `;'\n");
		return (1);
	}
	return (0);
}
