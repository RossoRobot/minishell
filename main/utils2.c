/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:27:51 by kbrauer           #+#    #+#             */
/*   Updated: 2024/04/19 12:00:48 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

/*
char    *skip_argument(char *str)
{
  while ((*str != 9 && *str != 10 && *str != 32) && *str)
		str++;
  return (str);
}
*/

char	*skip_gap(char *str)
{
	while ((*str == 9 || *str == 10 || *str == 32) && *str)
		str++;
	return (str);
}

char	*while_del(char *str)
{
	while (*str && (check_del(*str, 0) == 1))
		str++;
	return (str);
}

int	while_not_del(char *str, int flag, t_shell *shell, int *k)
{
	int	i;
	int	exp;
	int	len;

	i = 0;
	exp = 0;
	len = 0;
	while (str[i] && (check_del(str[i], flag) == 0) && str[i] != '\n')
	{
		if (str[i] == '$' && str[i + 1] != '\n' && str[i + 1] != '\0')
		{
			exp = expand(shell, &str[i + 1], &len);
			free(shell->exp_str);
			printf("while_not_del: %d\n", i);
			i = i +  (len - 1);
			printf("while_not_del: %d\n", i);
			printf("while_not_del: %d\n", len);
		}
		i++;
		set_flag(&str[i], &flag);
	}
	*k = i;
	return (i + exp - len);
}

void	set_flag(char *c, int *flag)
{
	if (*flag == 0 && *c == '\'')
	{
		*flag = 1;
		return;
	}
	else if (*flag == 0 && *c == '\"')
	{
		*flag = 2;
		return;
	}

	if (*flag == 1 && *c == '\'')
	{
		*flag = 0;
		return;
	}
	else if (*flag == 2 && *c == '\"')
	{
		*flag = 0;
		return;
	}
}

int	expand(t_shell *shell, char *str, int	*len)
{
	int	i;
	char *tmp;

	i = 0;
	while (str[i] != ' ' && str[i] != '\n' && str[i] != '\'' && str[i] != '\"' && str[i] != '\0')
		i++;
	tmp = (char *) malloc (sizeof(char) + (i + 1));
	if (!tmp)
		return(-1);
	i = 0;
	while (str[i] != ' ' && str[i] != '\n' && str[i] != '\'' && str[i] != '\"' && str[i] != '\0')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	*len = i + 1;
	shell->exp_str = my_getenv(shell, tmp, 1);
	if (!shell->exp_str)
		return (0);
	return (ft_strlen(shell->exp_str));
}
