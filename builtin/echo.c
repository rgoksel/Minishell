/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:12:44 by makbas            #+#    #+#             */
/*   Updated: 2023/10/03 17:43:14 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_char(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		write(STDOUT_FILENO, &(input[i]), 1);
		i++;
	}
}

int	echo_parameter(char **prm)
{
	int	i;
	int	j;

	i = 1;
	if (prm[1][0] != '-')
		return (1);
	while (prm[i])
	{
		j = 1;
		if (prm[i][0] == '-')
		{
			while (prm[i][j] == 'n')
				j++;
			if (prm[i][j] != '\0')
				return (i);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int	b_echo(char **input)
{
	int	i;
	int	flag;

	flag = TRUE;
	if (count_value(input) == 1)
		return (write(1, "\n", 1) - 1);
	i = echo_parameter(input);
	if (i > 1)
		flag = FALSE;
	while (input[i])
	{
		put_char(input[i]);
		if (input[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (flag)
		write(STDOUT_FILENO, "\n", 1);
	if (g_mshell.process_count == 1)
		errno = 0;
	if (!(is_parent()) || g_mshell.process_count != 1)
		exit(EXIT_SUCCESS);
	return (0);
}
