/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:01:54 by mvolgger          #+#    #+#             */
/*   Updated: 2024/04/23 19:59:44 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/builtins.h"

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

void	handle_empty_env(t_shell *data, char *key)
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

int	exit_code_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isnum(str[i] == 0))
			return(-1);
		i++;
	}
	return (0);
}
//dont forget to add in atoi to check until long long max?? or some kind of max

int	ft_exit(t_shell *shell, t_list *list)
{
	int	nr;

	nr = 0;
	if (list->next && list->next->next && list->next->next->next)
	{
		ft_putstr_fd("exit: too many arguments\n",2);
		return (-1);
	}
	if (exit_code_check(list->next->content) == -1)
	{
		ft_putstr_fd("exit: numeric argument required\n",2);
		return (-1);
	}
	if (list->next->content)
		nr = ft_atoi(list->next->content);
	free_parse(shell);
	free_exit(shell, 0);
	exit (nr);
}

