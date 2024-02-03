/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:05:31 by makbas            #+#    #+#             */
/*   Updated: 2023/10/05 17:13:39 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_error(int type)
{
	char	*red;

	if (type == HERE_DOC)
		red = "<<";
	else if (type == RED_INPUT)
		red = "<";
	else if (type == RED_OUTPUT)
		red = ">";
	else if (type == RED_APPEND)
		red = ">>";
	else if (type == PIPE)
		red = "|";
	else
		red = "newline";
	errno = 258;
	write(2, "minishell: syntax error near unexpected token '", 47);
	write(2, red, ft_strlen(red));
	write(2, "'\n", 2);
}

void	command_error(char *str)
{
	errno = 127;
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n", 20);
	if (!is_parent())
		exit(errno);
}

void	directory_error(char *str)
{
	errno = 126;
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": is a directory\n", 17);
	if (!is_parent())
		exit(errno);
}

int	error_pipe(void)
{
	printf("minishell: syntax error near unexpected token '|'\n");
	free_token();
	free_process();
	errno = 258;
	return (FALSE);
}

void	nofile_error(char *str, char *exe)
{
	if (ft_strchr(str, '/'))
		errno = 127;
	else
		errno = 1;
	write(2, exe, ft_strlen(exe));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 28);
	if (!is_parent())
		exit(errno);
}
