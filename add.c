/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:23 by makbas            #+#    #+#             */
/*   Updated: 2023/10/09 16:52:35 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		env_add_back(&g_mshell.env, new_env(ft_strdup(env[i])));
		i++;
	}
}

void	append_export(void)
{
	t_env	*env;

	env = g_mshell.env;
	while (env)
	{
		ex_add_back(&g_mshell.export, \
			new_ex(ft_strjoin_two(env->str)));
		env = env->next;
	}
}

int	ft_strcmp_path(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (FALSE);
	i = 0;
	while (i < 5)
	{
		if (s1[i] != s2[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	append_paths(void)
{
	char	*path;
	t_env	*env;

	env = g_mshell.env;
	path = NULL;
	while (env)
	{
		if (ft_strcmp_path(env->str, "PATH="))
		{
			path = env->str;
			break ;
		}
		env = env->next;
	}
	g_mshell.paths = ft_split(path, ':');
}

char	**append_envo(void)
{
	char	**envo;
	t_env	*temp;
	t_env	*temp1;
	int		i;
	int		len;

	temp = g_mshell.env;
	temp1 = g_mshell.env;
	i = -1;
	len = 0;
	while (temp1)
	{
		len++;
		temp1 = temp1->next;
	}
	envo = malloc(sizeof(char **) * len + 1);
	if (!envo)
		return (NULL);
	while (++i < len)
	{
		envo[i] = temp->str;
		temp = temp->next;
	}
	envo[i] = NULL;
	return (envo);
}
