/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:27:17 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/28 18:53:20 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void exit_hardcode234(t_shell *shell, t_list *list)
{
	if (list->next == NULL)
		return;
	list = list->next;
	if (list->content[0] == '\0')
	{
		ft_putstr_fd("exit\nminishell: exit: numeric argument required\n", 2);
		free_exit(shell, 2);
	}
	return ;
}

int	ft_exit(t_shell *shell, t_list *list)
{
	long	nr;

	nr = get_last_return_value(shell);

	if (list != NULL)
	{
		exit_hardcode234(shell, list);
		if (list->next != NULL)
		{
			if (exit_code_check(list->next->content) == -1 || (list->next
					&& (ft_atol(list->next->content) == LONG_MAX)))
			{
				exit_helper(shell, list->next->content, 1);
				free_exit(shell, 2);
				exit(2);
			}
		}
		if (list->next && list->next->next)
			return (exit_helper(shell, NULL, 0));
		if (list->next && list->next->content)
			nr = ft_atol(list->next->content);
	}
	printf("exit\n");
	free_exit(shell, nr);
	exit(nr);
}

void	reset_fds(t_shell *shell, int stdin_backup, int stdout_backup)
{
	if (dup2(stdin_backup, STDIN_FILENO) == -1)
	{
		free_exit(shell, 1);
	}
	close(stdin_backup);
	if (dup2(stdout_backup, STDOUT_FILENO) == -1)
	{
		close(stdin_backup);
		free_exit(shell, 1);
	}
	close(stdout_backup);
}

t_list	*find_command(t_list *list)
{
	t_list	*temp;
	t_list	*temp2;

	temp = list;
	while (temp != NULL)
	{
		if ((temp->type >= 10 && temp->type <= 16) || temp->type == 0
			|| temp->type == 2)
		{
			temp2 = temp;
			while (temp2 != NULL)
			{
				//set_type(temp2);
				temp2 = temp2->next;
			}
			return (temp);
		}
		if ((temp->type >= 4 && temp->type <= 7))
		{
			temp = temp->next;
		}
		temp = temp->next;
	}
	return (temp);
}

void	handle_shlvl(t_shell *data)
{
	char	*str;
	char	*value;

	str = NULL;
	value = NULL;
	str = my_getenv(data, "SHLVL", 0);
	if (!str)
		export_malloc(data, ft_strdup(data, "SHLVL=0"), NULL, NULL);
	else
		free(str);
}

int	is_n_flag(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
		{
			return (0);
		}
		i++;
	}
	if (i == 1)
		return (0);
	return (1);
}
