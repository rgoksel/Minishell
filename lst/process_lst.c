/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 00:01:39 by makbas            #+#    #+#             */
/*   Updated: 2023/10/02 12:05:14 by rdemiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_process	*new_process(void)
{
	t_process	*process;

	process = ft_calloc(sizeof(t_process), 1);
	pipe(process->fd);
	process->pid = -1;
	process->execute = ft_calloc(sizeof(char *), 1);
	process->redirects = ft_calloc(sizeof(char *), 1);
	process->prev = NULL;
	process->next = NULL;
	return (process);
}

void	process_add_back(t_process **process, t_process *new)
{
	t_process	*i_process;

	i_process = *process;
	if (!(i_process))
		*process = new;
	else
	{
		while (i_process->next)
			i_process = i_process->next;
		i_process->next = new;
		new->prev = i_process;
	}
}
