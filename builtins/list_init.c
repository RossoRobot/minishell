/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 08:21:43 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/20 21:26:25 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/builtins.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	if (!arr[i])
		return (free(arr));
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
	return ;
}

void	free_exit(t_shell *data, int error_flag)
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
	if (error_flag == 1408)
	{
		free(data);
		printf("exit\n");
		exit(0);
	}
	freeparse_or_not(data, error_flag);
}

void	freeparse_or_not(t_shell *shell, int flag)
{
	free(shell->pid);
	if (flag != 0)
	{
		free_parse(shell);
		free_hname2(shell);
		free(shell);
		close_all_fds();
		exit(flag);
	}
	else
	{
		free_parse(shell);
		free_hname2(shell);
		free(shell);
		close_all_fds();
		exit(flag);
	}
	return ;
}

void	first_node_init(t_shell *data, char *key, char *value, char *str)
{
	data->env_line = malloc(sizeof(t_env));
	if (!(data->env_line))
		free_exit(data, 138);
	data->env_line->previous = NULL;
	data->env_line->next = NULL;
	data->env_line->key_value = NULL;
	data->env_line->key_value = set_keys_n_values(data, key, value, str);
}
