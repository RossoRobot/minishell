/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:25:27 by mvolgger          #+#    #+#             */
/*   Updated: 2024/04/19 14:51:04 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "minishell.h"

typedef struct s_shell t_shell;

typedef struct	s_key_value
{
	char	*key;
	char	*value;
}				t_key_value;

typedef struct	s_env
{
	struct s_env	*next;
	struct s_env	*previous;	
	t_key_value		*key_value;
}				t_env;


int		pwd(t_shell *data);
char    *my_getenv(t_shell *data, char *str, int mallocflag);
int		change_directory(t_shell *data, char *parameter);
int		ft_cd(t_shell *data, char *parameter);
int		change_to_home(t_shell *data, char *oldpwd, char *parameter);

void	free_arr(char **arr);
size_t	count_strings(char **envp);

char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strdup(t_shell *data, const char *s);
char	*ft_strjoin(t_shell *data, char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

int		export(t_shell *data, char *str, char *key, char *value);
int		replace_var(t_shell *data, char *key, char *value, int key_malloc_flag);
int		unset(t_shell *data, char *str);
int		delete_node(t_env *node);
int		check_for_equal(char *str);

void	free_exit(t_shell *data, int error_flag);
char	*get_key(t_shell *data, char *str);
char	*get_value(t_shell *data, char *str);
void	first_node_init(t_shell *data, char *key, char *value, char *str);
void	append_node(t_shell *data, char *key, char *value, char *str, int flag);
void	env_duplicate(t_shell *data, char **envp);
int		check_missing_env(t_shell *data);
void	print_myenv(t_shell *data, int flag);
t_key_value	*set_keys_n_values(t_shell *data, char *key, char *value, char *str);
void	handle_empty_env(t_shell *data, char *key);

int		ft_listsize(t_env *myenv);
char	*join_key_value(t_env *temp, t_shell *data);
char	**transform_list_to_arr(t_shell *data, t_env *myenv);


#endif
