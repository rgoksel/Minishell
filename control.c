/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:13:55 by makbas            #+#    #+#             */
/*   Updated: 2023/10/02 12:01:17 by rdemiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirects(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '<' && str[1] == '<')
		return (HERE_DOC);
	if (str[0] == '>' && str[1] == '>')
		return (RED_APPEND);
	if (str[0] == '<')
		return (RED_INPUT);
	if (str[0] == '>')
		return (RED_OUTPUT);
	if (str[0] == '|')
		return (PIPE);
	return (0);
}

int	is_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	is_number(char *nbr)
{
	int	i;

	i = 0;
	while (nbr)
	{
		if (!(nbr[i] >= '0' && nbr[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

int	count_value(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
