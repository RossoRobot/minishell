/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:20:19 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/14 14:58:14 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/builtins.h"

char	*my_getenv(t_shell *data, char *str, int mallocflag)
{
	t_env	*temp;
	char	*env_value;

	if (str == NULL)
		return (NULL);
	temp = data->env_line;
	env_value = NULL;
	while (temp)
	{
		if (ft_strncmp(temp->key_value->key, str, ft_strlen(str)) == 0
			&& ft_strlen(str) == ft_strlen(temp->key_value->key))
		{
			env_value = ft_strdup(data, temp->key_value->value);
			if (mallocflag == 1)
				free_to_null(&str);
			return (env_value);
		}
		temp = temp->next;
	}
	return (NULL);
}

int	change_to_home(t_shell *data, char *oldpwd, char *parameter)
{
	char	*home;

	home = my_getenv(data, "HOME", 0);
	if (home == NULL)
	{
		return (printf("cd: HOME not set\n"), -1);
	}
	if (chdir(home) == -1)
	{
		printf("cd: HOME not set\n");
		free(home);
		return (-1);
	}
	else
	{
		replace_var(data, "OLDPWD", oldpwd, 0);
		replace_var(data, "PWD", home, 0);
		free(home);
		return (0);
	}
}
// does not work if parameter is not trimmed properly

int	change_directory(t_shell *data, char *parameter)
{
	if (parameter && ft_strncmp(".", parameter, ft_strlen(parameter)) == 0)
	{
		free(parameter);
		return (0);
	}
	else
		return (ft_cd(data, parameter));
}

int	ft_cd(t_shell *data, char *parameter)
{
	char	*old_pwd;
	int		ret;
	char	*path;

	ret = 0;
	old_pwd = my_getenv(data, "PWD", 0);
	if (parameter == NULL || parameter[0] == '\0' || parameter[0] == ' ')
	{
		ret = change_to_home(data, old_pwd, parameter);
		free(old_pwd);
	}
	else
	{
		ret = chdir(parameter);
		if (ret == -1)
		{
			free(old_pwd);
			printf("cd: no such file or directory: %s\n", parameter);
		}
		else
		{
			export_pwds(data, old_pwd);
			free(old_pwd);
		}
		free(parameter);
	}
	return (ret);
}

void	export_pwds(t_shell *data, char *old_pwd)
{
	char	*old_pwd_key;
	char	*pwd_key;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	old_pwd_key = ft_strdup(data, "OLDPWD");
	pwd_key = ft_strdup(data, "PWD");
	export(data, NULL, old_pwd_key, old_pwd);
	export(data, NULL, pwd_key, pwd);
	//free(old_pwd_key);
	free(pwd);
}

// int	export_oldpwd(t_shell *shell, char *old_pwd_key, char *old_pwd)
// {
// 	t_env *temp;

// 	temp = shell->env_line;
// 	while (temp != NULL)
// 	{
// 		if (ft_strncmp(temp->key_value->key, "OLDPWD"))
// 	}
// }
