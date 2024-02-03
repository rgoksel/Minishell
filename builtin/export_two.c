/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:28:48 by makbas            #+#    #+#             */
/*   Updated: 2023/10/09 16:46:06 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	show_export(void)
{
	t_export	*exp;

	exp = g_mshell.export;
	while (exp)
	{
		printf("%s\n", exp->str);
		exp = exp->next;
	}
}

void	update_export_equal(char *upt)
{
	t_export	*upt_ex;
	t_env		*upt_env;

	upt_ex = find_export(g_mshell.export, upt);
	upt_env = find_env(g_mshell.env, upt);
	free(upt_ex->str);
	if (upt_env == NULL)
		env_add_back(&g_mshell.env, new_env(ft_strdup(upt)));
	else
	{
		free(upt_env->str);
		upt_env->str = ft_strdup(upt);
	}
	upt_ex->str = ft_strdup_two(upt, 14, EQUAL);
}

void	update_export_value(char *upt)
{
	t_export	*upt_ex;
	t_env		*upt_env;

	upt_ex = find_export(g_mshell.export, upt);
	upt_env = find_env(g_mshell.env, upt);
	free(upt_ex->str);
	if (upt_env == NULL)
		env_add_back(&g_mshell.env, new_env(ft_strdup(upt)));
	else
	{
		free(upt_env->str);
		upt_env->str = ft_strdup(upt);
	}
	upt_ex->str = ft_strjoin_two(upt);
}
