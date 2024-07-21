/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:59:07 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/20 19:59:05 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	mal_list(t_shell *shell)
{
	shell->lists = (t_list **) malloc (sizeof(t_list *) * (shell->n_pipes + 2));
	if (!shell->lists)
		free_exit(shell, 1);
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
			printf(" type:  %d\n", ptr->type);
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
	int	flagflag;

	set_data(&i, &flag1, &flag2, shell);
	flagflag = 0;
	if (start_w_pipe(shell, str))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	while (str[i])
	{
		pipe_counter(shell, str[i], flag1, flag2);
		while (str[i] == '|')
			i++;
		if (!str[i])
			break ;
		increase_flag(str[i], &flag1, &flag2, &flagflag);
		i++;
	}
	if (flag1 % 2 || flag2 % 2)
		return (check_input_helper(shell), 1);
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
	define_type(shell);
	set_here_del_type(shell);
	if (expansion(shell))
		exit (1);
	sep_env_cmd(shell);
	print_tokens(shell);
	unquote(shell);
	if (start_w_pipe(shell, shell->lists[0]->content))
	{
		ft_putstr_fd("|: command not found\n", 2);
		return (1);
	}
	if (start_heredoc(shell))
		return (free_parse(shell), 1);
	trim_hedoc(shell);
	return (0);
}

void	set_here_del_type(t_shell *shell)
{
	t_list	*ptr;
	int		i;

	i = 0;
	if (!shell->lists)
		return ;
	ptr = shell->lists[i];
	while (ptr)
	{
		if (ptr->type == he_doc && ptr->next)
			ptr->next->type = here_del;
		ptr = ptr->next;
		if (!ptr)
			ptr = shell->lists[++i];
	}
	ptr = NULL;
}
