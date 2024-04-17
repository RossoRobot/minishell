/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:04:16 by mvolgger          #+#    #+#             */
/*   Updated: 2024/04/17 18:12:28 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*str;
	
	data = NULL;
	//str = ft_strdup(data, "..");
	data = malloc(sizeof(t_data));
	if (!data)
		free_exit(data, 1);
	data->env_line = NULL;
	data->env_arr = NULL;
	env_duplicate(data, envp);
	//print_myenv(data, 0);
	//export(data, str, NULL, NULL);
	// data->env_arr = transform_list_to_arr(data, data->env_line);
	// unset(data, str);
	change_directory(data, NULL);
	print_myenv(data, 0);
	//print_myenv(data, 1);
	// pwd(data);
	free_exit(data, 0);
	return (0);
}