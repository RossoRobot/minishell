/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:52:08 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/20 16:28:57 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtins.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

extern int					g_var;

# define DEL " |"

typedef struct s_env		t_env;
typedef struct s_key_value	t_key_value;

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
	he_doc_fin = 17,
}							t_tokentype;

typedef struct s_pids
{
	pid_t					*pid;
	struct t_pids			*next;
}							t_pids;

typedef struct s_token
{
	char					*str;
	t_tokentype				type;
}							t_token;

typedef struct s_herename
{
	char					*content;
	struct s_herename		*next;
}							t_hname;

typedef struct s_list
{
	char					*content;
	t_tokentype				type;
	struct s_list			*next;
}							t_list;

typedef struct s_shell
{
	int						n_pipes;
	int						h_lines;
	char					**str;
	char					*exp_str;
	char					**env_arr;
	int						last_return_value;
	int						flag;
	bool					sig_flag;
	int						del_flag;
	int						heredoc_flag;
	int						stdin_backup;
	int						stdout_backup;
	int						fd[2];
	t_env					*env_line;
	t_list					**lists;
	t_hname					*hname;
}							t_shell;

// main2
int							first_init(t_shell *shell, int argc, char **argv);
int							init_values(t_shell *shell);
void						test_malloc(t_shell *shell);
void						check_input_helper(t_shell *shell);
void						define_type_helper(t_list *ptr);

// parse
int							parse(char *cmd, t_shell *shell);
int							check_input(char *str, t_shell *shell);
void						print_tokens(t_shell *shell);
void						create_tokens(char *input, t_shell *shell);
void						mal_list(t_shell *shell);

// parse2
t_shell						*set_data_return_shell(t_shell *shell, int *i,
								int *k, int *pipes);
int							while_pipe(char *input, int *flag);
void						increase_i_decrease_pipes(int *i, int *pipes);
int							set_input(char **input);
int							start_w_pipe(t_shell *shell, char *str);

// expansion
int							expansion(t_shell *shell);
int							mal_dollar(t_shell *shell, char *str);
char						*replace_dollar(t_shell *shell, char *str, int len);
int							replace_dollar_str(t_shell *shell, char *tmp);

// expansion2
int							expand_str(t_shell *shell, int *n, t_list *ptr);
int							replace_dollar_helper(int *n, int *i, int *flag,
								int len);
int							check_shlvl(char *str);

// helper
void						set_exp_str(t_shell *shell, char *tmp);

// sep_env_cmd
int							squeeze_node(t_list *ptr, char *content);
int							split_token(t_list *ptr, int n);
int							sep_env_cmd(t_shell *shell);
void						negative_fd(t_shell *shell, int fd);
void						newl_numl(int *flag, int fd, int *num_lines,
								char *cmd);

// signal
void						recieve_signal(t_shell *shell, int flag,
								int shellflag, char *str);
void						handler(int sig);
void						heredoc_helper(t_shell *shell, char *content,
								t_list *ptr, char *tmp);

// utils
t_list						*ft_lstnew(char *content, int *k, t_shell *shell);
void						ft_lstadd_back(t_list *lst, t_list *neu);
int							chk_del(t_shell *shell, char *chr, int *flag,
								int pos);
t_hname						*ft_lstnew_hdoc(t_shell *shell, void *content);
void						ft_lstadd_back_hdoc(t_hname *lst, t_hname *new);

// utils2
char						*skip_gap(char *str);
char						*while_del(t_shell *shell, char *str);
int							while_not_del(char *str, int *flag, t_shell *shell,
								int *k);
void						set_flag(char *c, int *flag);

// define_type
int							set_type(t_list *node);
int							set_type2(t_list *node);
void						define_type(t_shell *shell);
t_list						*define_flag(t_list *ptr);
int							check_n_flag(char *str);

// unquote
int							unquote(t_shell *shell);
int							check_for_quote(int flag, char c, int tmp,
								char *content);
t_list						**set_data(int *i, int *tmp, int *flag,
								t_shell *shell);
char						*del_quote(char *str);

// heredoc
int							start_heredoc(t_shell *shell);
char						*here_doc(t_shell *shell, char *arg);
void						del_next_node(t_list *ptr);
char						*add_hname(t_shell *shell);
void						trim_hedoc(t_shell *shell);

// heredoc2
int							cmd_is_null_or_del(char *cmd, int fd, char *arg,
								t_shell *shell);
int							no_del(t_list *ptr);
void						handle_node(t_shell *shell, t_list *ptr, char *tmp);
void						set_flag_and_num_lines(int *flag, int *num_lines);
char						*check_g_var(t_shell *shell, int fd);

// set_return_value
int							set_return_value(t_shell *shell, int retval);
int							increase_flag(char c, int *f1, int *f2, int *ff);
void						pipe_counter(t_shell *s, char c, int f1, int f2);
int							write_free(int fd, char **cmd);
void						count_lines_newl(t_shell *s, int l, int f, int fd);

// free
t_list						*free_parse_helper(t_list *ptr, char *content,
								t_list *list);
void						free_parse(t_shell *shell);
void						free_to_null(char **var);
void						free_hname(t_shell *shell);
void						free_hname2(t_shell *shell);

// execute
int							execute(t_shell *shell);
int							prepare_execution(t_shell *shell, t_list *list);
int							child_process(t_shell *shell, t_list *list);
int							execute_builtin(t_shell *shell, t_list *list);
int							execute_no_pipe(t_shell *shell, t_list *list);
char						**transform_list(t_shell *shell, t_list *list);
int							execute_binary(t_shell *shell, t_list *list);
t_list						*find_command(t_list *list);
void						check_some_things(t_shell *shell, t_list *list);

char						**ft_split(const char *s1, char c);
char						*path_access(t_shell *shell, t_list *list,
								char **arr);
char						*get_path(t_shell *shell, t_list *list);

int							execute_no_pipe(t_shell *shell, t_list *list);
void						execute_onechild(t_shell *shell, t_list *list,
								int *fd);
int							execute_command(t_shell *shell, t_list *list);

// child_processes
void						first_child_process(t_shell *shell, t_list *list,
								int *pipes, int temp_fd);
void						last_child_process(t_shell *shell, t_list *list,
								int *pipes, int temp_fd);
int							forkex(t_shell *shell, int temp_fd);

void						pick_child_process(t_shell *shell, int i,
								int *pipes, int temp_fd);

void						close_fds(t_shell *shell, int *fd, int temp_fd);

void						wait_for_child(t_shell *shell, int flag, int pid);

void						no_pipe_child(t_shell *shell, t_list *list);

// redirections
int							is_redirection(t_shell *shell, t_list *list);
void						prep_redir_exec(t_shell *shell, t_list *list,
								int flag);
int							exec_redir(t_shell *shell, t_list *temp, char **arr,
								t_list *list);
int							redirect_input(t_shell *shell, t_list *list,
								char **arr, t_list *list_begin);
int							redirect_output(t_shell *shell, t_list *list,
								char **arr, int append);
int							execute_it(t_shell *shell, char **arr,
								t_list *list);

void						reset_fds(t_shell *shell, int stdin_backup,
								int stdout_backup);

int							is_n_flag(char *str);

int							cmd_position(t_list *list);

void						dup_stds(t_shell *shell);

void						freeparse_or_not(t_shell *shell, int flag);

int							check_last_node(t_list *list, int flag);

void						close_all_fds(void);

char						*create_shlvl(t_shell *data, char *envp);

int							get_last_return_value(t_shell *shell);

#endif