/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:04:16 by mvolgger          #+#    #+#             */
/*   Updated: 2024/04/17 16:25:18 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*str;
	
	data = NULL;
	//str = ft_strdup(data, "hello");
	data = malloc(sizeof(t_data));
	if (!data)
		free_exit(data, 1);
	data->env_line = NULL;
	data->env_arr = NULL;
	env_duplicate(data, envp);
	//print_myenv(data, 0);
	export(data, NULL, NULL, NULL);
	// data->env_arr = transform_list_to_arr(data, data->env_line);
	// print_myenv(data, 0);
	// unset(data, NULL);
	// change_directory(data, str);
	print_myenv(data, 0);
	//pwd(data);
	free_exit(data, 0);
	return (0);
}