/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:59:07 by kbrauer           #+#    #+#             */
/*   Updated: 2024/06/20 17:09:36 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	mal_list(t_shell *shell)
{
	shell->lists = (t_list **) malloc (sizeof(t_list *) * (shell->n_pipes + 2));
	if (!shell->lists)
		return ;
	shell->lists[shell->n_pipes + 1] = NULL;
}

void	create_tokens(char *input, t_shell *shell)
{
	int		i;
	int		k;
	int		flag;
	int		pipes;

	mal_list(set_data_return_shell(shell, &i, &k, &pipes));
	while (pipes + 1)
	{
		input = skip_gap(input);
		shell->lists[i] = ft_lstnew(input, &k, shell);
		while (*input)
		{
			while (k-- != 0)
				input++;
			flag = set_input(&input);
			if (*input == 0)
				break ;
			if (*input == '|')
				input += while_pipe(input, &flag);
			if (flag)
				break ;
			ft_lstadd_back(shell->lists[i], ft_lstnew(input, &k, shell));
		}
		increase_i_decrease_pipes(&i, &pipes);
	}
}

void	print_tokens(t_shell *shell)
{
	t_list	*ptr;
	int		i;

	i = 0;
	while (shell->lists[i])
	{
		ptr = shell->lists[i];
		while (ptr)
		{
			printf("content: %s\n", ptr->content);
			printf("   type:  %d\n", ptr->type);
			ptr = ptr->next;
		}
		i++;
	}
	ptr = NULL;
}

int	check_input(char *str, t_shell *shell)
{
	int	i;
	int	flag1;
	int	flag2;

	set_data(&i, &flag1, &flag2, shell);
	if (start_w_pipe(shell, str))
		return (1);
	while (str[i])
	{
		if (str[i] == '|')
		{
			while (str[i] == '|')
				i++;
			shell->n_pipes++;
		}
		if (!str[i])
			break ;
		flag1 += increase_flag(str[i], '\"');
		flag2 += increase_flag(str[i], '\'');
		i++;
	}
	if (flag1 % 2 || flag2 % 2)
	{
		printf("minishell: error: invalid number of quotation\n");
		set_return_value(shell, 0);
		free_exit(shell, 0);
		exit(0);
	}
	return (0);
}

int	parse(char *cmd, t_shell *shell)
{
	init_values(shell);
	if (check_input(cmd, shell))
		return (1);
	create_tokens(cmd, shell);
	if (!shell->lists)
		return (1);
	if (expansion(shell))
		exit (1);
	sep_env_cmd(shell);
	define_type(shell);
	unquote(shell);
	if (start_w_pipe(shell, shell->lists[0]->content))
		return (1);
	if (start_heredoc(shell))
		return (free_parse(shell), 1);
	trim_hedoc(shell);
	return (0);
}
