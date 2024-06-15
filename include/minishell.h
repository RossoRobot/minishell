/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:52:08 by kbrauer           #+#    #+#             */
/*   Updated: 2024/05/28 11:29:53 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include "builtins.h"

extern int g_var;

//delimiter characters
# define DEL " |"

typedef	struct s_env t_env;
typedef struct s_key_value t_key_value;

typedef enum e_tokentype
{
	command_a = 0,
	metachar_a = 1,
	text_a = 2,
	flag_a = 3,
	re_in = 4,
	re_out = 5,
	he_doc = 6,
	out_app = 7,
	delete_a = 8,
	echo_a = 10,
	cd_a = 11,
	pwd_a = 12,
	export_a = 13,
	unset_a = 14,
	env_a = 15,
	exit_a = 16,
}	t_tokentype;

typedef	struct 	s_pids
{
	pid_t			*pid;
	struct t_pids 	*next;
}	t_pids;

typedef struct s_token
{
	char		*str;
	t_tokentype	type;
}	t_token;

typedef struct s_herename
{
	char				*content;
	struct s_herename	*next;
}	t_hname;

typedef struct s_list
{
	char			*content;
	t_tokentype		type;
	struct s_list	*next;
}	t_list;

typedef struct s_shell
{
	int			n_pipes;
	int			h_lines;
	char 		**str;
	char		*exp_str;
	char		**env_arr;
	int			last_return_value;
	t_env		*env_line;
	pid_t		*pids;
	t_list		**lists;
	t_hname		*hname;
}	t_shell;

//main2
int		first_init(t_shell *shell);
int		init_values(t_shell *shell);

//parse
int 	parse(char *cmd, t_shell *shell);
int		check_input(char *str, t_shell *shell);
void 	print_tokens(t_shell *shell);
void	create_tokens(char *input, t_shell *shell);
void	mal_list(t_shell *shell);

//parse2
t_shell	*set_data_return_shell(t_shell *shell, int *i, int *k, int *pipes);
int		while_pipe(char *input, int *flag);
void	increase_i_decrease_pipes(int *i, int *pipes);
int		set_input(char **input);

//expansion
int		expansion(t_shell *shell);
int		mal_dollar(t_shell *shell, char *str);
char	*replace_dollar(t_shell *shell, char *str, int len);
int		replace_dollar_str(t_shell *shell, char *tmp);

//expansion2
int		expand_str(t_shell *shell, int *n, t_list *ptr);
int		replace_dollar_helper(int *n, int *i, int *flag, int len);

//sep_env_cmd
int		squeeze_node(t_list *ptr, char *content);
int		split_token(t_list *ptr, int n);
int		sep_env_cmd(t_shell *shell);

//utils
t_list	*ft_lstnew(char *content, int *k, t_shell *shell);
void	ft_lstadd_back(t_list *lst, t_list *neu);
int		check_del(char	chr, int flag);
t_hname	*ft_lstnew_hdoc(t_shell *shell, void *content);
void	ft_lstadd_back_hdoc(t_hname *lst, t_hname *new);

//utils2
char    *skip_gap(char *str);
char  	*while_del(char *str);
int 	while_not_del(char *str, int *flag, t_shell *shell, int *k);
void 	set_flag(char *c, int *flag);

//define_type
int		set_type(t_list *node);
int		set_type2(t_list *node);
void    define_type(t_shell *shell);
t_list	*define_flag(t_list *ptr);
int		check_n_flag(char *str);

//unquote
int		unquote(t_shell *shell);
int		check_for_quote(int flag, char c, int tmp, char *content);
t_list	**set_data(int *i, int *tmp, int *flag, t_shell *shell);
char	*del_quote(char *str);

//heredoc
int		start_heredoc(t_shell *shell);
char	*here_doc(t_shell *shell, char *arg);
void	del_next_node(t_list *ptr);
char	*add_hname(t_shell *shell);
void	trim_hedoc(t_shell *shell);

//heredoc2
int		cmd_is_null_or_del(char *cmd, int fd, char *arg, t_shell *shell);
int		no_del(t_list *ptr);
void	handle_node(t_list *ptr, char *tmp);
void	set_flag_and_num_lines(int *flag, int *num_lines);
char	*check_g_var(t_shell *shell, int fd, char *hname);

//set_return_value
int		set_return_value(t_shell *shell, int retval);
int		increase_flag(char c, char d);

//store_pid
int		count_pids(pid_t *pid_arr);
int		copy_pids(pid_t *old_pids, pid_t *new_pids, pid_t pid);
int		store_pid(t_shell *shell, pid_t pid);

//free
t_list	*free_parse_helper(t_list *ptr, char *content, t_list *list);
void    free_parse(t_shell *shell);
void	free_to_null(char **var);
void	free_hname(t_shell *shell);

//execute
int		execute(t_shell *shell);
int		prepare_execution(t_shell *shell, t_list *list);
void	child_process(t_shell *shell, t_list *list);
int		execute_builtin(t_shell *shell, t_list *list);
int		execute_no_pipe(t_shell *shell, t_list *list);
char	**transform_list(t_shell *shell, t_list *list);
int		execute_binary(t_shell *shell, t_list *list);

char	**ft_split(const char *s1, char c);
char    *path_access(t_shell *shell, t_list *list, char **arr);
char    *get_path(t_shell *shell, t_list *list);

int		execute_no_pipe(t_shell *shell, t_list *list);
void	execute_onechild(t_shell *shell, t_list *list, int *fd);
int		execute_command(t_shell *shell, t_list *list);

//child_processes
void	first_child_process(t_shell *shell, t_list *list, int *pipes, int temp_fd);
void	last_child_process(t_shell *shell, t_list *list, int *pipes, int temp_fd);
int		forkex(t_shell *shell);

//redirections
int 	is_redirection(t_shell *shell, t_list *list);
void    prep_redir_exec(t_shell *shell, t_list *list);
void    exec_redir(t_shell *shell, t_list *temp, char **arr, t_list *list);
void    redirect_input(t_shell *shell, t_list *list);
void 	redirect_output(t_shell *shell, t_list *list, int append);
int    execute_it(t_shell *shell, char **arr, t_list *list, int stdin_backup, int stdout_backup);
void    reset_fds(int stdin, int stdout);

# endif