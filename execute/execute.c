/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:28:17 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/27 17:27:08 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	execute_builtin(t_shell *shell, t_list *list)
{
	t_list	*temp;
	int		ret;

	temp = list;
	ret = 0;
	if (temp->type == export_a)
		ret = execute_export(shell, temp);
	if (temp->type == env_a)
		ret = execute_env(shell, temp);
	if (temp->type == unset_a)
		ret = execute_unset(shell, temp);
	if (temp->type == cd_a)
		ret = execute_cd(shell, temp);
	if (temp->type == pwd_a)
		ret = pwd(shell);
	if (temp->type == exit_a)
		ret = ft_exit(shell, list);
	if (temp->type == echo_a)
		ret = execute_echo(shell, temp);
	set_return_value(shell, ret);
	return (ret);
}

int	child_process(t_shell *shell, t_list *list)
{
	int	ret;

	ret = 0;
	if (list->type >= 10 && list->type <= 15)
	{
		ret = execute_builtin(shell, list);
	}
	else
		ret = execute_binary(shell, list);
	return (ret);
}

char	**transform_list(t_shell *shell, t_list *list)
{
	t_list	*temp;
	char	**arr;
	int		i;
	int		j;

	temp = list;
	i = 0;
	j = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	temp = list;
	arr = (char **)malloc(sizeof(char *) * (i + 1));
	if (!arr)
		free_exit(shell, 0);
	arr[i] = NULL;
	while (j < i)
	{
		arr[j] = ft_strdup(shell, temp->content);
		temp = temp->next;
		j++;
	}
	return (arr);
}

void	check_some_things(t_shell *shell, t_list *list)
{
	if (list->content[0] == '|' || list->content[0] == ';')
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		write(2, &list->content[0], 1);
		ft_putstr_fd("'\n", 2);
		free_exit(shell, 0);
		exit(2);
	}
}
