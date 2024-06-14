/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:30:33 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/14 12:32:19 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/builtins.h"

int	delete_node(t_env *node)
{
	t_env	*temp;
	t_env	*temp2;

	if (node == NULL)
		return (-1);
	temp = node->previous;
	temp2 = node->next;
	if (temp2 == NULL && temp != NULL)
		temp->next = NULL;
	else if (temp == NULL && temp2 != NULL)
		temp2->previous = NULL;
	else if (temp != NULL && temp2 != NULL)
	{
		temp->next = temp2;
		temp2->previous = temp;
	}
	free(node->key_value->key);
	if (node->key_value->value)
		free(node->key_value->value);
	free(node->key_value);
	free(node);
	return (0);
}

int	unset(t_shell *data, char *str)
{
	int		flag;
	t_env	*temp;

	if (str == NULL)
		return (-1);
	flag = check_for_equal(str);
	temp = data->env_line;
	while (temp != NULL)
	{
		if (ft_strncmp(str, temp->key_value->key, ft_strlen(str)) == 0
			&& flag == 0 && ft_strlen(str) == ft_strlen(temp->key_value->key))
		{
			if (temp->previous == NULL && temp->next != NULL)
				data->env_line = data->env_line->next;
			else if (temp->previous == NULL && temp->next == NULL)
				data->env_line = NULL;
			return (delete_node(temp));
		}
		temp = temp->next;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && (*s1 != '\0' || *s2 != '\0'))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

t_key_value	*set_keys_n_values(t_shell *data, char *key, char *value, char *str)
{
	t_key_value	*key_value_pair;

	key_value_pair = malloc(sizeof(t_key_value));
	if (!key_value_pair)
		free_exit(data, 1);
	key_value_pair->key = NULL;
	key_value_pair->value = NULL;
	if (key)
	{
		key_value_pair->key = ft_strdup(data, key);
		key_value_pair->value = ft_strdup(data, value);
		// free(key);
		// free(value);
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
