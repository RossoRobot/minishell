/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:13:29 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/12 16:33:00 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/builtins.h"

int	replace_var(t_shell *data, char *key, char *value, int key_malloc_flag)
{
	t_env	*temp;

	temp = data->env_line;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key_value->key, key,
				ft_strlen(temp->key_value->key)) == 0
			&& ft_strlen(temp->key_value->key) == ft_strlen(key))
		{
			if (key_malloc_flag == 1)
				free(key);
			// if (key_malloc_flag != 3)
			// 	free(temp->key_value->value);
			if (value == NULL)
				temp->key_value->value = NULL;
			else
			{
				free(temp->key_value->value);
				temp->key_value->value = ft_strdup(data, value);
			}
			return (0);
		}
		temp = temp->next;
	}
	return (-1);
}

int	check_export_str(t_shell *data, char *str)
{
	int	flag;

	flag = 0;
	if (ft_isalpha(*str) == 0 && (*str) != '_')
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'  not a valid identifier\n", 2);
		flag = 1;
	}
	while (*str != '=' && *str == '\0')
	{
		if ((ft_isalnum(*str == 1) && (*(str++)) && (*(str++) == ' ')))
			flag = 1;
		str++;
	}
	if (*str == '=' && *(str++) == ' ')
		flag = 1;
	if (flag == -1)
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'  not a valid identifier\n", 2);
	}
	return (flag);
}

int	export(t_shell *data, char *str, char *key, char *value)
{
	if ((!str && !key) || (str && str[0] == '\0'))
	{
		print_myenv(data, 1);
		return (0);
	}
	if (str)
	{
		if (check_export_str(data, str) == -1)
			return (-1);
		key = get_key(data, str);
		value = get_value(data, str);
		if (!value && check_for_equal(str) == 0)
		{
			append_node(data, key, value, str);
			return (0);
		}
	}
	if (replace_var(data, key, value, 1) == 0)
		return (0);
	else
		append_node(data, key, value, str);
	return (0);
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
