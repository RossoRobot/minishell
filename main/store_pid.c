/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_pid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:54:59 by kbrauer           #+#    #+#             */
/*   Updated: 2024/05/23 16:55:00 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	print_pids(t_shell* shell)
{
	int	i;

	i = 0;
	if (!shell->pids)
		return;
	while(shell->pids[i])
		printf("PIDs: %d\n", shell->pids[i++]);
}

int	count_pids(pid_t *pid_arr)
{
	int	i;

	i = 0;
	if (pid_arr == 0)
		return (0);
	while (pid_arr[i])
		i++;
	return (i);
}

int	copy_pids(pid_t *old_pids, pid_t *new_pids, pid_t pid)
{
	int	i;

	while (old_pids[i])
	{
		new_pids[i] = old_pids[i];
		i++;
	}
	new_pids[i] = pid;
	new_pids[++i] = 0;
	printf("copy_pids new_pids: %d\n", new_pids[0]);
	return (0);
}

int	store_pid(t_shell *shell, pid_t pid)
{
	pid_t	*new_pids;
	if (pid == 0)
		return (0);
	if (!shell->pids)
	{
		shell->pids = (pid_t*) malloc (sizeof(pid_t) * 2);
		if (!shell->pids)
			return (1);
		shell->pids[0] = pid;
		shell->pids[1] = 0;
		//printf("store_pid 1shell.pids: %d\n", shell->pids[0]);
	}
	else
	{
		new_pids = (pid_t*) malloc (sizeof(pid_t) * (count_pids(shell->pids) + 2));
		if (!new_pids)
			return (1);
		copy_pids(shell->pids, new_pids, pid);
		free(shell->pids);
		shell->pids = new_pids;
		//printf("store_pid 2shell.pids: %d\n", shell->pids[0]);
		//printf("store_pid 2new_pids: %d\n", new_pids[0]);
	}
	//print_pids(shell);
	return (0);
}
