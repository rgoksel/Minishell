/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:19:45 by rdemiray          #+#    #+#             */
/*   Updated: 2023/10/12 17:00:29 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*tmp_dup(char *env)
{
	char	*tmp;

	tmp = NULL;
	if (env[0] == '?')
		tmp = ft_itoa(errno);
	else if (ft_strncmp(env, "0", 1) == 0)
		tmp = ft_strdup("bash");
	else
		tmp = ft_strdup("$");
	return (tmp);
}

char	*env_add(char *env)
{
	char	*path;
	t_env	*environment;
	char	*tmp;

	tmp = NULL;
	environment = g_mshell.env;
	env = ft_strjoin(env, "=");
	while (environment)
	{
		if (ft_strncmp(environment->str, env, ft_strlen(env)) == 0)
		{
			path = environment->str;
			while (*path != '=')
				path++;
			path++;
			free(env);
			return (path);
		}
		environment = environment->next;
	}
	tmp = tmp_dup(env);
	free(env);
	return (tmp);
}

void	env_control(char *token, char **str, int *token_i, int *str_i)
{
	char	*env;
	int		start;
	int		len;
	char	*tmp;
	int		i;

	start = *token_i;
	len = get_env_length(token, token_i);
	env = ft_substr(token, start, len);
	tmp = env_add(env);
	free(env);
	if (tmp && tmp[0] == DOLLAR)
		free(tmp);
	else
	{
		i = 0;
		while (tmp && tmp[i])
		{
			(*str)[*str_i] = tmp[i];
			(*str_i)++;
			i++;
		}
		if (ft_strchr("0123456789b$", tmp[0]))
			free(tmp);
	}
}

int	quote_control(char *quote)
{
	int	count;
	int	i;
	int	s;
	int	f;

	s = 0;
	f = 0;
	i = -1;
	count = 0;
	while (quote[i++] != DOLLAR)
	{
		if (quote[i] == SINGLE_QUOTE)
			s++;
	}
	while (quote[i++])
	{
		if (quote[i] == SINGLE_QUOTE)
			f++;
	}
	count = s + f;
	if (((count % 2 == 0) && (s % 2 == 1)) || ((f == 1) && (s == 1)))
		return (0);
	if (count == 0)
		return (1);
	return (1);
}

char	*dollar_control(char *token)
{
	int		token_i;
	int		str_i;
	char	*str;
	int		i;

	str_i = 0;
	token_i = 0;
	if (ft_strchr(token, DOLLAR) && quote_control(token))
	{
		i = token_len(token);
		str = ft_calloc(sizeof(char), (i + 1));
		while (token[token_i])
		{
			if (token[token_i] == DOLLAR)
			{
				token_i++;
				env_control(token, &str, &token_i, &str_i);
			}
			else
				copy_characters(&str, &str_i, token, &token_i);
		}
		return (str);
	}
	return (ft_strdup(token));
}
