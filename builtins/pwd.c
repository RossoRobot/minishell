/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:12:54 by mvolgger          #+#    #+#             */
/*   Updated: 2024/04/16 14:41:33 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//change printf with ft_putstr or ft_putendl


int	pwd(t_data *data)
{
	char	*pwd;
	char	*temp;

	pwd = getcwd(NULL, 0);
	temp = NULL;
	if (!pwd)
	{
		temp = my_getenv(data, "PWD", 0);
		printf("%s\n", temp);
		free(temp);
		return (1);
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	return(0);
}

