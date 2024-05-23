/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:42:50 by mvolgger          #+#    #+#             */
/*   Updated: 2024/05/23 17:09:43 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int is_redirection(t_shell *shell, t_list *list)
{
    t_list  *temp;
    int     ret;

    ret = 0;
    temp = list;
    while (temp)
    {
        if (temp->type == 4 || temp->type == 5 || temp->type == 7)
            ret++;
        temp = temp->next;
    }
    return (ret);
}

void    prep_redir_exec(t_shell *shell, t_list *list)
{
    t_list *temp;
    char    **cmd_arr;
    int     i;
    int     j;
    
    i = 0;
    j = 0;
    temp = list;
    while (temp != NULL && temp->type != 4 && temp->type != 5 && temp->type != 7)
    {
        i++;
        temp = temp->next;
    }
    cmd_arr = (char **)malloc(sizeof(char *) * (i + 1));
    if (!cmd_arr)
        free_exit(shell, 1);
    cmd_arr[i] = NULL;
    temp = list;
    while (j < i)
    {
        cmd_arr[j] = ft_strdup(shell, temp->content);
        temp = temp->next;
        j++;
    }
    temp = list;
    exec_redir(shell, temp, cmd_arr, list);
}

void    exec_redir(t_shell *shell, t_list *temp, char **arr, t_list *list)
{
    int stdin_backup;
    int stdout_backup;
   
    stdin_backup = dup(STDIN_FILENO);
    stdout_backup = dup(STDOUT_FILENO);
    while (temp != NULL)
    {
        while (temp != NULL && temp->type != 4 && temp->type != 5 && temp->type != 7)
            temp = temp->next;
        if (temp == NULL)
        {
            execute_it(shell, arr, list, stdin_backup, stdout_backup);
            break ;
        }
        else if (temp->type == 5)
            redirect_output(shell, temp->next);
        else if (temp->type == 4)
            redirect_input(shell, temp->next);
        temp = temp->next;
    }
}

void    reset_fds(int stdin, int stdout)
{
    dup2(stdin, STDIN_FILENO);
    close(stdin);
    dup2(stdout, STDOUT_FILENO);
    close(stdout);
}
int    execute_it(t_shell *shell, char **arr, t_list *list, int stdin_backup, int stdout_backup)
{
    char    *path;

    if (list->type >= 10 && list->type <= 16)
    {
        execute_builtin(shell, list);
        reset_fds(stdin_backup, stdout_backup);
        return (0);
    }
    path = get_path(shell, list);
    shell->env_arr = transform_list_to_arr(shell, shell->env_line);
	if (!(shell->env_arr))
        free_exit(shell, 1);
    if (execve(path, arr, shell->env_arr) == -1)
    {
        free(path);
        free_arr(arr);
        free_arr(shell->env_arr);
    }
    return (0);
}

void    redirect_input(t_shell *shell, t_list *list)
{
    int fd;

    fd = open(list->content, O_RDONLY);
    if (fd == -1)
    {
        ft_putstr_fd("no such file or directory: ", 2);
        ft_putstr_fd(list->content ,2);
        ft_putstr_fd("\n", 2);
        exit(-1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
}

void redirect_output(t_shell *shell, t_list *list)
{
    int fd;

    fd = open(list->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        ft_putstr_fd(list->content ,2);
        ft_putstr_fd(": permission denied\n", 2);
        exit (-1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
}