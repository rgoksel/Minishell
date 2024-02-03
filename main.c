/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:00:32 by makbas            #+#    #+#             */
/*   Updated: 2023/10/12 16:32:35 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_cmd(void)
{
	t_process	*process;

	process = g_mshell.process;
	close_all_fd();
	while (process)
	{
		if (process->pid != -1)
		{
			waitpid(process->pid, &errno, 0);
			errno = WEXITSTATUS(errno);
		}
		process = process->next;
	}
}

void	init_env(char **env)
{
	pid_t	child_pid;
	char	**op;

	errno = 0;
	g_mshell.paths = NULL;
	append_env(env);
	op = malloc(3 * sizeof(char *));
	op[0] = malloc(strlen("unset ") + 1);
	op[1] = malloc(strlen("OLDPWD") + 1);
	ft_strcpy(op[0], "export ");
	ft_strcpy(op[1], "OLDPWD");
	op[2] = NULL;
	b_unset(op);
	free_array(op);
	append_export();
	append_paths();
	child_pid = fork();
	if (child_pid == 0)
		exit(1);
	else
	{
		g_mshell.parent_pid = child_pid - 1;
		wait(NULL);
	}
}

void	start_cmd(void)
{
	t_process	*process;

	process = g_mshell.process;
	if (!process)
		return ;
	is_heredoc();
	if (g_mshell.ignore)
		return (close_all_fd());
	if (g_mshell.quit)
		write(1, "\033[A\033[K", 7);
	if (is_builtin(process->execute[0]) && g_mshell.process_count == 1)
	{
		get_builtin(process);
		process = process->next;
	}
	while (process)
	{
		run_cmd(process);
		process = process->next;
	}
	wait_cmd();
}

void	launch_ms(char *input)
{
	t_token		*token;
	t_process	*process;

	token = NULL;
	process = NULL;
	g_mshell.process_count = 0;
	g_mshell.token = NULL;
	g_mshell.process = NULL;
	tokenize(input);
	if (!lexerize(token, process))
		return ;
	g_mshell.flag = 1;
	start_cmd();
	free_process();
	add_history(input);
}

int	main(int ac, char **av, char **env)
{
	char	*input;

	init_env(env);
	while (ac && av)
	{
		g_mshell.quit = 0;
		g_mshell.flag = 0;
		g_mshell.ignore = FALSE;
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, sig_quit_handler);
		input = readline("MinisHELL$ ");
		ctrl_d(input);
		if (g_mshell.ignore)
		{
			free(input);
			input = malloc(1);
			errno = 1;
		}
		if (*input)
			launch_ms(input);
		free(input);
	}
	exit(errno);
}
