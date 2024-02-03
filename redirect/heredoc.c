/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:12:18 by makbas            #+#    #+#             */
/*   Updated: 2023/10/09 16:49:37 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_heredoc(int sig)
{
	(void)sig;
	g_mshell.ignore = TRUE;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	start_heredoc(int *heredoc_fd, char *end_str)
{
	char		*input;

	if (pipe(heredoc_fd) < 0)
		return (perror("minishell"));
	while (1)
	{
		signal(SIGINT, &close_heredoc);
		input = readline("> ");
		if (!input || ft_strcmp(input, end_str) || g_mshell.ignore)
		{
			free(input);
			break ;
		}
		write(heredoc_fd[1], input, ft_strlen(input));
		write(heredoc_fd[1], "\n", 1);
		free(input);
	}
	close(heredoc_fd[1]);
}

void	is_heredoc(void)
{
	int			i;
	char		**redirects;
	t_process	*process;

	process = g_mshell.process;
	while (process)
	{
		i = 0;
		redirects = process->redirects;
		while (redirects[i] && !(g_mshell.ignore))
		{
			if (is_redirects(redirects[i]) == HERE_DOC)
				start_heredoc(process->heredoc_fd, redirects[i + 1]);
			i += 2;
		}
		process = process->next;
	}
}
