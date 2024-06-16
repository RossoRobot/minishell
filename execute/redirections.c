/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:42:50 by mvolgger          #+#    #+#             */
/*   Updated: 2024/06/16 15:42:55 by mvolgger         ###   ########.fr       */
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
            return ;
        }
        else if (temp->type == 5)
            redirect_output(shell, temp->next, 0);
        else if (temp->type == 7)
            redirect_output(shell, temp->next, 1);
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
t_list  *find_command(t_list *list)
{
    t_list *temp;
    t_list *temp2;

    temp = list;
    while (temp != NULL)
    {
        if ((temp->type >= 10 && temp->type <= 16) || temp->type == 0 || temp->type == 2)
        {
            temp2 = temp;
            while(temp2 != NULL)
            {
                set_type(temp2);
                temp2 = temp2->next;
            }
            return (temp);
        }
        if ((temp->type >= 4 && temp->type <= 7))
        {
            temp = temp->next;
        }
        temp = temp->next;
    }
    return (temp);
}

int    execute_it(t_shell *shell, char **arr, t_list *list, int stdin_backup, int stdout_backup)
{
    char    *path;
    t_list  *temp;

    temp = find_command(list);
    if (temp->type >= 10 && temp->type <= 16)
    {
        free_arr(arr);
        execute_builtin(shell, temp);
        reset_fds(stdin_backup, stdout_backup);   
        exit (0);
    }
    path = get_path(shell, temp);
    shell->env_arr = transform_list_to_arr(shell, shell->env_line);
	if (!(shell->env_arr))
        free_exit(shell, 1);
    if (execve(path, arr, shell->env_arr) == -1)
    {
        free(path);
        //free_arr(arr);
        //free_arr(shell->env_arr);
        ft_putstr_fd(temp->content, 2);
        ft_putstr_fd(": command not found\n", 2);
        free_exit(shell, 1);
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

void redirect_output(t_shell *shell, t_list *list, int append)
{
    int fd;

    if (append == 0)
        fd = open(list->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (append == 1)
        fd = open(list->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        ft_putstr_fd(list->content ,2);
        ft_putstr_fd(": permission denied\n", 2);
        exit (-1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
}