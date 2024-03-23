/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:52:08 by kbrauer           #+#    #+#             */
/*   Updated: 2024/03/09 18:49:14 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
//#include "./libft_bonus/libft.h"

//delimiter characters
# define DEL " "

typedef enum e_tokentype
{
	command = 0,
	metachar = 1,
	text = 2,
}	t_tokentype;

// typedef struct s_token
// {
// 	char		*str;
// 	t_tokentype	type;
// }	t_token;

typedef struct s_list
{
	char			*content;
	t_tokentype		type;
	struct s_list	*next;
}					t_list;

typedef struct s_shell
{
	char 	**str;
	int		n_pipes;
	t_list	*tokens;
	t_list	**lists;
}	t_shell;


//main
//int	create_tokens(char *cmd, t_shell *shell);

//utils
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list *lst, t_list *neu);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		check_del(char	chr);

//free
void    free_all(t_shell *shell);

#endif