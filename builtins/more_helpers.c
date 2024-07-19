/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:15:27 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/25 11:39:29 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/builtins.h"

size_t	count_strings(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

long	ft_atol(char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
			return (LONG_MAX);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	check_for_equal(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (-1);
	while (str[i] != '\0')
		i++;
	i--;
	if (str[i] == '=')
		return (1);
	return (0);
}

int	check_missing_env(t_shell *data)
{
	t_env	*temp;
	int		counter;

	counter = 4;
	temp = data->env_line;
	if (temp == NULL)
		return (-1);
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key_value->key, "PWD", 3) == 0
			|| ft_strncmp(temp->key_value->key, "_", 1) == 0
			|| ft_strncmp(temp->key_value->key, "SHLVL", 5) == 0
			|| ft_strncmp(temp->key_value->key, "last_return_value", 18) == 0)
			counter--;
		temp = temp->next;
	}
	if (counter == 0)
		return (0);
	else
		return (-1);
}

char	*create_shlvl(t_shell *data, char *envp)
{
	char	*shlvl;
	char	*key;

	shlvl = NULL;
	key = ft_strdup(data, "SHLVL");
	shlvl = increment_shlvl(data, envp);
	append_node(data, key, shlvl, NULL);
	free(key);
	free(shlvl);
	return ("SHLVL=");
}
