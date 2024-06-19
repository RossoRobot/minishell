/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:24:37 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/14 11:30:28 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/builtins.h"

void	print_myenv(t_shell *data, int flag)
{
	t_env	*temp;

	temp = data->env_line;
	while (data->env_line != NULL)
	{
		if (flag == 1 && ft_strncmp(data->env_line->key_value->key,
				"lrv", 8) != 0)
		{
			printf("declare -x %s", data->env_line->key_value->key);
			if (data->env_line->key_value->value != NULL)
				printf("=\"%s\"\n", data->env_line->key_value->value);
			else
				printf("\n");
		}
		else if (flag == 0 && data->env_line->key_value->value
			&& ft_strncmp(data->env_line->key_value->key, "lrv",
				8) != 0)
		{
			printf("%s=", data->env_line->key_value->key);
			printf("%s\n", data->env_line->key_value->value);
		}
		data->env_line = data->env_line->next;
	}
	data->env_line = temp;
}
