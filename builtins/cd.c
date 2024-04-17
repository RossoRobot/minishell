/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:47:16 by mvolgger          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/17 18:02:51 by mvolgger         ###   ########.fr       */
=======
/*   Updated: 2024/04/17 15:47:26 by mvolgger         ###   ########.fr       */
>>>>>>> 57b07bd9a25e71403bf9dd8030676d3841294eb5
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char    *my_getenv(t_data *data, char *str, int mallocflag)
{
    t_env   *temp;
	char	*env_value;

	if (str == NULL)
		return (NULL);
    temp = data->env_line;
	env_value = NULL;
    while (temp)
    {
        if (ft_strncmp(temp->key_value->key, str, ft_strlen(str)) == 0 && ft_strlen(str) == ft_strlen(temp->key_value->key))
		{
			env_value = ft_strdup(data, temp->key_value->value);
			if (mallocflag == 1)
				free(str);
			return (env_value);
		}
        temp = temp->next; 
    }
	return (NULL);
}
int	change_to_home(t_data *data, char *oldpwd, char *parameter)
{
	char	*home;
	
	home = my_getenv(data, "HOME", 0);
	if (home == NULL)
	{
		free(oldpwd);
		return (printf("cd: no such file or directory: HOME\n"), -1);
	}
	if (chdir(home) == -1)
	{
		printf("cd: no such file or directory: %s\n", "HOME");
		free(oldpwd);
		free(home);
		return (-1);
	}
	else
	{
		replace_var(data, "OLDPWD", oldpwd, 0);
		replace_var(data, "PWD", home, 0);
		return (0);
	}
}
//does not work if parameter is not trimmed properly

int	change_directory(t_data *data, char *parameter)
{
	
	if (parameter && ft_strncmp(".", parameter, ft_strlen(parameter)) == 0)
	{
		free(parameter);
		return (0);
	}
	else
		return(ft_cd(data, parameter));
}

int	ft_cd(t_data *data, char *parameter)
{
	char 	*old_pwd;
	int		ret;
    char	*path;

	ret = 0;
	old_pwd = my_getenv(data, "PWD", 0);
	if (parameter == NULL || parameter[0] == '\0' || parameter[0] == ' ')
		ret = change_to_home(data, old_pwd, parameter);
    else
    {
        ret = chdir(parameter);
		if (ret == -1)
		{
			free(old_pwd);
        	printf("cd: no such file or directory: %s\n", parameter);
			free(parameter);
		}
        else
        {
            replace_var(data, "OLDPWD", old_pwd, 0);
			replace_var(data, "PWD", parameter, 0);
			free(old_pwd);
			if (ft_strncmp(parameter, "..", 2) == 0)
				replace_var(data, "PWD", getcwd(NULL, 0), 0);
        }
    }
	return (ret);
} 



