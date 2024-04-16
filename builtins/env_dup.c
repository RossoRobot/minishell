/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:01:54 by mvolgger          #+#    #+#             */
/*   Updated: 2024/04/16 10:47:07 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// duplicate the env so its possible to manipulate it

size_t	count_strings(char **envp)
{
	size_t	i;

	i = 0;
	while(envp[i] != NULL)
		i++;
	return (i);
}
// handle the case when i run the program with env -i (deleting the env)

void	handle_empty_env(t_data *data)
{
	char	*pwd;
	char	*pwd_str;

	pwd = getcwd(NULL, 0);
	pwd_str = ft_strjoin(data, "PWD=", pwd);
	free(pwd);
	append_node(data, NULL, NULL, pwd_str, 1);
	append_node(data, NULL, NULL, "SHLVL=1", 0);
	append_node(data, NULL, NULL,"_=/usr/bin/env", 0);
}

