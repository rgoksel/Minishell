/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:06:24 by makbas            #+#    #+#             */
/*   Updated: 2023/10/02 13:44:02 by rdemiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_write(char *str)
{
	int		i;
	char	*path;
	t_env	*env;

	i = 0;
	str = ft_strjoin(str, "=");
	env = g_mshell.env;
	while (env)
	{
		if (ft_strncmp(env->str, str, ft_strlen(str)) == 0)
		{
			path = env->str;
			str = ft_substr(path, ft_strlen(str), \
				ft_strlen(path) - ft_strlen(str));
			printf("%s\n", str);
			return ;
		}
		env = env->next;
	}
	nofile_error(g_mshell.process->execute[1], "env");
}

void	empty_env1(t_env *env)
{
	env = g_mshell.env;
	while (env)
	{
		printf("%s\n", env->str);
		env = env->next;
	}
}

int	b_env(void)
{
	t_env	*env;
	char	**exe;
	char	*path;
	char	**envo;

	env = g_mshell.env;
	exe = g_mshell.process->execute;
	if (!exe[1])
		empty_env1(env);
	else if (exe[1] && exe[1][0] == '$' && !exe[2])
		env_write(exe[1]);
	else if (exe[1] && !exe[2] && access(exe[1], F_OK) == 0)
	{
		envo = append_envo();
		path = get_path("sh");
		execve(path, g_mshell.process->execute, envo);
		free_array(envo);
	}
	else if ((exe[1] && !exe[2] && access(exe[1], F_OK) == -1))
		nofile_error(exe[1], exe[0]);
	if (!is_parent())
		exit (EXIT_SUCCESS);
	return (0);
}
