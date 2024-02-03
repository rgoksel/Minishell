/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:09:01 by makbas            #+#    #+#             */
/*   Updated: 2023/10/03 19:32:19 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_dir(char *cmd)
{
	DIR	*dir;

	if (!cmd)
		exit(EXIT_SUCCESS);
	dir = opendir(cmd);
	if (dir && readdir(dir))
	{
		closedir(dir);
		directory_error(cmd);
	}
}

char	*search_path(char *cmd, char **paths)
{
	char	*new_cmd;
	char	*path;

	new_cmd = ft_strjoin("/", cmd);
	while (*paths)
	{
		path = ft_strjoin(*paths, new_cmd);
		if (!access(path, F_OK))
		{
			free(new_cmd);
			return (path);
		}
		free(path);
		paths++;
	}
	if (path && ft_strchr(cmd, '/'))
		nofile_error(cmd, "minishell:");
	free(new_cmd);
	return (NULL);
}

char	*get_path(char *cmd)
{
	char	**paths;

	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	check_dir(cmd);
	append_paths();
	paths = g_mshell.paths;
	if (!paths)
		command_error(cmd);
	return (search_path(cmd, paths));
}
