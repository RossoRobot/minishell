/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:47:52 by mvolgger          #+#    #+#             */
/*   Updated: 2024/02/29 14:04:58 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>


void	input_handler(char *str)
{
	
}

int	main()
{
	char	*input;
	while (1)
	{
		input = readline("minishell$ ");
		if (strcmp(input, "exit") == 0)
			break ;
		else 
			input_handler(input);
	}
	return (0);
}