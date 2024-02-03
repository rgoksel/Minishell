/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:53:58 by makbas            #+#    #+#             */
/*   Updated: 2023/10/02 12:05:04 by rdemiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*tmp_env;

	tmp_env = *env;
	if (!tmp_env)
		*env = new;
	else
	{
		while (tmp_env->next)
			tmp_env = tmp_env->next;
		tmp_env->next = new;
	}
}

t_env	*new_env(char *str)
{
	t_env	*env;

	env = ft_calloc(sizeof(t_env), 1);
	env->str = str;
	env->next = NULL;
	return (env);
}

t_env	*find_env(t_env *env, char *find)
{
	t_env	*environment;

	environment = env;
	if (!environment)
		return (0);
	while (environment)
	{
		if (ft_strcmp_env(environment->str, find))
			return (environment);
		environment = environment->next;
	}
	return (0);
}
