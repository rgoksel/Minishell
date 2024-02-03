/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:18:13 by makbas            #+#    #+#             */
/*   Updated: 2023/10/02 13:40:35 by rdemiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	old_pwd(void)
{
	char	*str;
	char	*old_pwd;
	char	**op;

	old_pwd = getcwd(NULL, 0);
	str = ft_strjoin("OLDPWD=", old_pwd);
	op = malloc(3 * sizeof(char *));
	if (op == NULL)
		exit(EXIT_FAILURE);
	op[0] = malloc(strlen("export ") + 1);
	op[1] = malloc(strlen(str) + 1);
	if (op[0] == NULL || op[1] == NULL)
		exit(EXIT_FAILURE);
	ft_strcpy(op[0], "export ");
	ft_strcpy(op[1], str);
	op[2] = NULL;
	b_export(op);
	free(old_pwd);
	free_array(op);
	free(str);
}

void	update_pwd(void)
{
	char	*str;
	char	*pwd;
	char	**op;

	pwd = getcwd(NULL, 0);
	str = ft_strjoin("PWD=", pwd);
	op = malloc(3 * sizeof(char *));
	if (!op)
		exit(EXIT_FAILURE);
	op[0] = malloc(strlen("export ") + 1);
	op[1] = malloc(strlen(str) + 1);
	if (op[0] == NULL || op[1] == NULL)
		exit(EXIT_FAILURE);
	ft_strcpy(op[0], "export ");
	ft_strcpy(op[1], str);
	op[2] = NULL;
	b_export(op);
	free(pwd);
	free_array(op);
	free(str);
}

int	b_cd(void)
{
	char	*arg;

	arg = g_mshell.process->execute[1];
	old_pwd();
	if (arg == NULL)
	{
		errno = 1;
		chdir(getenv("HOME"));
		return (0);
	}
	if (chdir(arg) != 0)
	{
		nofile_error(arg, "minishell");
		return (1);
	}
	update_pwd();
	return (0);
	if (!is_parent())
		exit (errno);
}
