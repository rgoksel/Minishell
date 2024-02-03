/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:00:25 by makbas            #+#    #+#             */
/*   Updated: 2023/10/02 12:20:00 by rdemiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *input)
{
	char	**cmd;
	int		i;

	cmd = malloc(sizeof(char *) * 8);
	cmd[0] = "cd";
	cmd[1] = "exit";
	cmd[2] = "unset";
	cmd[3] = "export";
	cmd[4] = "env";
	cmd[5] = "pwd";
	cmd[6] = "echo";
	cmd[7] = NULL;
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd[i], input))
		{
			free(cmd);
			return (1);
		}
		i++;
	}
	free(cmd);
	return (0);
}

void	run_builtin(t_process *process)
{
	char	*exe;
	char	**input;

	exe = process->execute[0];
	input = process->execute;
	if (ft_strcmp(exe, "cd"))
		b_cd();
	if (ft_strcmp(exe, "pwd"))
		b_pwd();
	if (ft_strcmp(exe, "exit"))
		b_exit();
	if (ft_strcmp(exe, "env"))
		b_env();
	if (ft_strcmp(exe, "echo"))
		b_echo(input);
	if (ft_strcmp(exe, "export"))
		b_export(input);
	if (ft_strcmp(exe, "unset"))
		b_unset(input);
}
