/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:01:54 by mvolgger          #+#    #+#             */
/*   Updated: 2024/04/17 18:21:49 by mvolgger         ###   ########.fr       */
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

void	handle_empty_env(t_data *data, char *key)
{
	char	*pwd;
	char	*pwd_str;
	char	*shlvl;
	char	*lst_cmd;

	pwd = getcwd(NULL, 0);
	pwd_str = ft_strjoin(data, "PWD=", pwd);
	shlvl = ft_strdup(data, "SHLVL=1");
	lst_cmd = ft_strdup(data, "_=/usr/bin/env");
	
	free(key);
	free(pwd);
	export(data, pwd_str, NULL, NULL);
	export(data, shlvl, NULL, NULL);
	export(data, lst_cmd, NULL, NULL);

}

