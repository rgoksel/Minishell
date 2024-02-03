/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:33:07 by makbas            #+#    #+#             */
/*   Updated: 2023/10/03 18:10:33 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	b_exit(void)
{
	char	**exe;
	int		count;

	exe = g_mshell.process->execute;
	count = 0;
	while (exe[count])
		count++;
	if (count == 1 || (count == 2 && (ft_atoi(exe[1]))))
	{
		write(1, "exit\n", 5);
		exit(errno);
	}
	else if (count > 2 && (ft_atoi(exe[1])))
	{
		errno = 1;
		write(1, "exit\nMinishell: exit: too many arguments\n", 41);
	}
	else if (!(is_number(exe[1])))
	{
		printf("exit\nMinishell: exit: %s: numeric argument required\n" \
			, exe[1]);
		exit(-1 % 256);
	}
	return (0);
}
