/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:01:54 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/07 11:45:50 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/builtins.h"

void	handle_empty_env(t_shell *data)
{
	char	*pwd;
	char	*pwd_str;
	char	*lst_cmd;
	char	*last_return_value;

	pwd = getcwd(NULL, 0);
	pwd_str = ft_strjoin(data, "PWD=", pwd);
	free(pwd);
	lst_cmd = ft_strdup(data, "_=/usr/bin/env");
	last_return_value = ft_strdup(data, "lrv=0");
	export_malloc(data, pwd_str, NULL, NULL);
	export_malloc(data, lst_cmd, NULL, NULL);
	export_malloc(data, last_return_value, NULL, NULL);
	add_oldpwd(data);
}

void	add_oldpwd(t_shell *data)
{
	char	*pwd;
	char	*pwd_str;

	pwd = getcwd(NULL, 0);
	pwd_str = ft_strjoin(data, "OLDPWD=", pwd);
	free(pwd);
	export_malloc(data, pwd_str, NULL, NULL);
}

int	export_malloc(t_shell *data, char *str, char *key, char *value)
{
	if (check_export_str(data, str) == -1)
	{
		free(str);
		return (-1);
	}
	key = get_key(data, str);
	value = get_value(data, str);
	free(str);
	if (!value && check_for_equal(str) == 0)
	{
		append_node(data, key, value, str);
		free(key);
		free(value);
		return (0);
	}
	if (replace_var(data, key, value, 1) == 0)
		return (free(value), 0);
	else
	{
		append_node(data, key, value, NULL);
		free(key);
		free(value);
	}
	return (0);
}

int	exit_code_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isnum(str[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_exit(t_shell *shell, t_list *list)
{
	long	nr;

	nr = 0;
	if (list != NULL)
	{
		if (list->next != NULL)
		{
			if (exit_code_check(list->next->content) == -1 || (list->next
					&& (ft_atol(list->next->content) == LONG_MAX)))
			{
				exit_helper(shell, list->next->content, 1);
				free_exit(shell, 2);
				exit(2);
			}
		}
		if (list->next && list->next->next)
			return (exit_helper(shell, NULL, 0));
		if (list->next && list->next->content)
			nr = ft_atol(list->next->content);
	}
	free_exit(shell, nr);
	free_parse(shell);
	free(shell);
	printf("exit\n");
	exit(nr);
}
