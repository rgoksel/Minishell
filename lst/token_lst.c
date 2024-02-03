/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:15:28 by makbas            #+#    #+#             */
/*   Updated: 2023/10/02 12:05:17 by rdemiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_add_back(t_token **token, t_token *new, int plus)
{
	t_token	*tmp_token;

	tmp_token = *token;
	if (!tmp_token)
		*token = new;
	else
	{
		while (tmp_token->next)
			tmp_token = tmp_token->next;
		tmp_token->next = new;
		new->prev = tmp_token;
	}
	return (plus);
}

t_token	*new_token(char *str, enum e_token_type type)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	token->str = str;
	token->type = type;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}
