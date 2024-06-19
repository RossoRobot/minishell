/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:01:54 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/19 14:54:59 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/builtins.h"

// duplicate the env so its possible to manipulate it

size_t	count_strings(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}
// handle the case when i run the program with env -i (deleting the env)

void	handle_empty_env(t_shell *data, char *key)
{
	char	*pwd;
	char	*pwd_str;
	char	*shlvl;
	char	*lst_cmd;
	char	*last_return_value;
	char	*dummy;

	dummy = key;
	pwd = getcwd(NULL, 0);
	pwd_str = ft_strjoin(data, "PWD=", pwd);
	free(pwd);
	shlvl = ft_strdup(data, "SHLVL=1");
	lst_cmd = ft_strdup(data, "_=/usr/bin/env");
	last_return_value = ft_strdup(data, "lrv=0");
	export_malloc(data, pwd_str, NULL, NULL);
	export_malloc(data, lst_cmd, NULL, NULL);
	export_malloc(data, shlvl, NULL, NULL);
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
			free(key);
			free(value);
			return (0);
		}
		free(str);
	}
	if (replace_var(data, key, value, 1) == 0)
	{
		free(value);
		return (0);
	}
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
// dont forget to add in atoi to check until long long max?? or some kind of max

int	ft_exit(t_shell *shell, t_list *list)
{
	long	nr;

	nr = 0;
	if (list != NULL)
	{
		if (list->next && list->next->next)
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (-1);
		}
		if (list->next != NULL)
		{
			if (exit_code_check(list->next->content) == -1 || (list->next
				&& (ft_atol(list->next->content) == LONG_MAX)))
			{
				free_parse(shell);
				free_exit(shell, 0);
				ft_putstr_fd("exit: numeric argument required\n", 2);
				exit(2);
			}
		}
		if (list->next && list->next->content)
			nr = ft_atol(list->next->content);
	}
	free_parse(shell);
	free_exit(shell, 0);
	exit(nr);
}

long	ft_atol(char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
			return (LONG_MAX);
		result = result * 10 + (str[i] + '0');
		i++;
	}
	return (result * sign);
}
