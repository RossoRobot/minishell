/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:30:03 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/14 10:50:18 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/builtins.h"

int	ft_listsize(t_env *myenv)
{
	int		i;
	t_env	*temp;

	i = 0;
	if (!myenv)
		return (0);
	temp = myenv;
	while (myenv != NULL)
	{
		i++;
		myenv = myenv->next;
	}
	myenv = temp;
	return (i);
}

char	*join_key_value(t_env *temp, t_shell *data)
{
	char	*str;
	char	*keytemp;

	str = NULL;
	keytemp = ft_strjoin(data, temp->key_value->key, "=");
	str = ft_strjoin(data, keytemp, temp->key_value->value);
	free(keytemp);
	return (str);
}

char	**transform_list_to_arr(t_shell *data, t_env *myenv)
{
	char	**arr;
	t_env	*temp;
	int		i;
	int		j;

	i = ft_listsize(myenv);
	j = 0;
	temp = myenv;
	arr = (char **)malloc(sizeof(char *) * (i + 1));
	if (arr == NULL)
		free_exit(data, 1);
	arr[i] = NULL;
	while (j < i)
	{
		arr[j] = join_key_value(temp, data);
		if (!arr[j])
			free_exit(data, 1);
		temp = temp->next;
		j++;
	}
	return (arr);
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
			append_node(data, key, shlvl, NULL);
			i++;
		}
		append_node(data, NULL, NULL, envp[i]);
		i++;
	}
	if (check_missing_env(data) == -1)
		handle_empty_env(data, key);
}
