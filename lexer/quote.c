/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:05:28 by makbas            #+#    #+#             */
/*   Updated: 2023/10/07 15:20:35 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*take_sub_text(char *str, int *i, char type)
{
	int		start;
	char	*new;

	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != type)
		(*i)++;
	new = ft_substr(str, start, *i - start);
	if (str[*i])
		(*i)++;
	return (new);
}

char	*take_text(char *str, int *i)
{
	int		start;
	char	*new;

	start = *i;
	while (str[*i] && str[*i] != DOUBLE_QUOTE && str[*i] != SINGLE_QUOTE)
		(*i)++;
	new = ft_substr(str, start, *i - start);
	return (new);
}

void	add_text(char **array, char *new)
{
	char	*arr_tmp;

	arr_tmp = *array;
	if (!(*array))
	{
		*array = ft_strdup(new);
		free(new);
		return ;
	}
	*array = ft_strjoin(*array, new);
	free(new);
	free(arr_tmp);
}

char	*clear_quote(char *token)
{
	char	*array;
	char	*new;
	int		i;

	i = 0;
	array = NULL;
	token = dollar_control(token);
	while (token[i])
	{
		if (token[i] == DOUBLE_QUOTE)
		{
			new = take_sub_text(token, &i, DOUBLE_QUOTE);
		}
		else if (token[i] == SINGLE_QUOTE)
		{
			new = take_sub_text(token, &i, SINGLE_QUOTE);
		}
		else
		{
			new = take_text(token, &i);
		}
		add_text(&array, new);
	}
	free(token);
	return (array);
}
