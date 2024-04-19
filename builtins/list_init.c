/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 08:21:43 by mvolgger          #+#    #+#             */
/*   Updated: 2024/04/19 14:52:02 by mvolgger         ###   ########.fr       */
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
	free(arr);
	return ;
}

void	free_exit(t_shell *data, int error_flag)
{
	t_env	*temp;

	while (data->env_line != NULL)
	{
		temp = data->env_line;
		if (temp->key_value->key)
			free(temp->key_value->key);
		if (temp->key_value->value)
			free(temp->key_value->value);
		if (temp->key_value)
			free(temp->key_value);
		data->env_line = data->env_line->next;
		if (temp)
			free(temp);
	}
	free_arr(data->env_arr);
	free(data);
	if (error_flag == 1)
		exit(EXIT_FAILURE);
}
void	first_node_init(t_shell *data, char *key, char *value, char *str)
{
	data->env_line = malloc(sizeof(t_env));
	if (!(data->env_line))
		free_exit(data, 1);
	data->env_line->previous = NULL;
	data->env_line->next = NULL;
	data->env_line->key_value = set_keys_n_values(data, NULL, NULL, str);
}
char	*get_key(t_shell *data, char *str)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		free_exit(data, 1);
	key[i] = '\0';
	while (j < i)
	{
		key[j] = str[j];
		j++;
	}
	return (key);
}

char	*get_value(t_shell *data, char *str)
{
	int		i;
	int		j;
	char	*start;
	char	*value;

	i = 0;
	j = 0;
	start = ft_strchr(str, '=');
	if (start == 0)
		return (NULL);
	start++;
	while (start[i] != '\0' && start[i] != ' ')
		i++;
	if (i == 0)
	{
		value = ft_strdup(data, "");
		return (value);
	}
	value = (char *)malloc(sizeof(char) * (i + 1));
	if (!value)
		free_exit(data, 1);
	ft_strlcpy(value, start, i + 1);
	return (value);
}

t_key_value	*set_keys_n_values(t_shell *data, char *key, char *value, char *str)
{
	t_key_value	*key_value_pair;

	key_value_pair = malloc(sizeof(t_key_value));
	if (!key_value_pair)
	{
		// add free(key) and value
		free_exit(data, 1);
	}
	key_value_pair->key = NULL;
	key_value_pair->value = NULL;
	if (key)
	{
		key_value_pair->key = ft_strdup(data, key);
		key_value_pair->value = ft_strdup(data, value);
		free(key);
		free(value);
		return (key_value_pair);
	}
	else if (str)
	{
		key_value_pair->key = get_key(data, str);
		key_value_pair->value = get_value(data, str);
		return (key_value_pair);
	}
	return (key_value_pair);
}

void	append_node(t_shell *data, char *key, char *value, char *str, int flag)
{
	t_env	*temp;

	temp = data->env_line;
	if (!temp)
		first_node_init(data, NULL, NULL, str);
	else
	{
		while (data->env_line->next != NULL)
			data->env_line = data->env_line->next;
		data->env_line->next = malloc(sizeof(t_env));
		if (!(data->env_line->next))
			free_exit(data, 1);
		data->env_line->next->previous = data->env_line;
		data->env_line = data->env_line->next;
		data->env_line->key_value = set_keys_n_values(data, key, value, str);
		if (flag == 1)
			free(str);
		if (!(data->env_line->key_value))
			free_exit(data, 1);
		data->env_line->next = NULL;
		data->env_line = temp;
	}
}

char	*increment_shlvl(t_shell *data, char *str)
{
	char	*value;
	int		temp;

	if (!str)
		return (NULL);
	value = get_value(data, str);
	if (!value)
		free_exit(data, 1);
	temp = ft_atoi(value) + 1;
	free(value);
	value = ft_itoa(temp);
	if (!value)
		free_exit(data, 1);
	return (value);
}
int	check_missing_env(t_shell *data)
{
	t_env	*temp;
	int		counter;

	counter = 3;
	temp = data->env_line;
	if (temp == NULL)
		return (-1);
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key_value->key, "PWD", 3) == 0
			|| ft_strncmp(temp->key_value->key, "_", 1) == 0
			|| ft_strncmp(temp->key_value->key, "SHLVL", 5) == 0)
			counter--;
		temp = temp->next;
	}
	if (counter == 0)
		return (0);
	else
		return (-1);
}

void	env_duplicate(t_shell *data, char **envp)
{
	int		i;
	char	*shlvl;
	char	*key;

	i = 0;
	shlvl = NULL;
	key = ft_strdup(data, "SHLVL");
	if (!envp || !envp[i])
	{
		handle_empty_env(data, key);
		return ;
	}
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			shlvl = increment_shlvl(data, envp[i]);
			append_node(data, key, shlvl, NULL, 0);
			i++;
		}
		append_node(data, NULL, NULL, envp[i], 0);
		i++;
	}
	if (check_missing_env(data) == -1)
		handle_empty_env(data, key);
}

void	print_myenv(t_shell *data, int flag)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = data->env_line;
	while (data->env_line != NULL)
	{
		i++;
		if (flag == 1)
		{
			printf("declare -x ");
			printf("%s", data->env_line->key_value->key);
			if (data->env_line->key_value->value != NULL)
				printf("=\"%s\"\n", data->env_line->key_value->value);
			else
				printf("\n");
		}
		else if (flag == 0 && data->env_line->key_value->value)
		{
			printf("%s=", data->env_line->key_value->key);
			printf("%s\n", data->env_line->key_value->value);
		}
		data->env_line = data->env_line->next;
	}
	data->env_line = temp;
}
