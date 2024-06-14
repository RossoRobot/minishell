/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:12:54 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/14 17:13:46 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/builtins.h"

int	pwd(t_shell *data)
{
	char	*pwd;
	char	*temp;

	pwd = getcwd(NULL, 0);		
	temp = NULL;
	if (!pwd)
	{
		temp = my_getenv(data, "PWD", 0);
		printf("%s\n", temp);
		ft_putstr_fd("pwd: cannot access parent directories: No such file or directory\n", 2);
		free(temp);
		return (1);
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	return (0);
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
	while (start[i] != '\0')
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


void	append_node(t_shell *data, char *key, char *value, char *str)
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
