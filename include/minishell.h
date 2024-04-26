/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:52:08 by kbrauer           #+#    #+#             */
/*   Updated: 2024/04/22 20:45:27 by mvolgger         ###   ########.fr       */
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
# include <sys/types.h>
# include "builtins.h"
# include <sys/wait.h>

//delimiter characters
# define DEL " "

typedef	struct s_env t_env;
typedef struct s_key_value t_key_value;

typedef enum e_tokentype
{
	command_a = 0,
	metachar_a = 1,
	text_a = 2,
	flag_a = 3,
	echo_a = 10,
	cd_a = 11,
	pwd_a = 12,
	export_a = 13,
	unset_a = 14,
	env_a = 15,
	exit_a = 16,
}	t_tokentype;

typedef struct s_token
{
	char		*str;
	t_tokentype	type;
}	t_token;

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
	t_env	*env_line;
	char	**env_arr;
	char	*exp_str;
	t_list	**lists;
}	t_shell;

//parse
int 	parse(char *cmd, t_shell *shell);
int		init_values(t_shell *shell);
int		check_input(char *str, t_shell *shell);
void 	print_tokens(t_shell *shell);
void	create_tokens(char *input, t_shell *shell);
void	mal_list(t_shell *shell);

//utils
t_list	*ft_lstnew(char *content, int *k, t_shell *shell);
void	ft_lstadd_back(t_list *lst, t_list *neu);

// int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		check_del(char	chr, int flag);

//utils2
char    *skip_argument(char *str);
char    *skip_gap(char *str);
char  	*while_del(char *str);
int 	while_not_del(char *str, int flag, t_shell *shell, int *k);
void 	set_flag(char *c, int *flag);
int		expand(t_shell *shell, char *str, int	*flag);

//define_type
int		set_type(t_list *node);
int		set_type2(t_list *node);
void    define_type(t_shell *shell);

int	check_input(char *str, t_shell *shell);
int	init_values(t_shell *shell);
int parse(char *cmd, t_shell *shell);
void	create_tokens(char *input, t_shell *shell);
void	mal_list(t_shell *shell);

//free
void    free_parse(t_shell *shell);

//execute
int	execute(t_shell *shell);
int	prepare_execution(t_shell *shell, t_list *list);
void	child_process(t_shell *shell, t_list *list, int *fd);
int	execute_builtin(t_shell *shell, t_list *list);
int	execute_no_pipe(t_shell *shell, t_list *list);

#endif