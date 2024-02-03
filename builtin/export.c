/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:20:09 by makbas            #+#    #+#             */
/*   Updated: 2023/10/09 16:44:02 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_control(char *str)
{
	int	i;
	int	equal_i;
	int	len;
	int	value;

	len = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			equal_i = i;
		i++;
	}
	if (!(equal_i >= 1))
		equal_i = -1;
	value = -1;
	if (ft_strchr(EX_CTRL, str[0]))
		value = ERROR;
	else if (equal_i == -1)
		value = VARIABLE;
	else if (equal_i + 1 == len)
		value = EQUAL;
	else if (equal_i + 1 < len)
		value = VALUE;
	return (value);
}

void	new_value_export(char *new, int choose)
{
	t_export	*upt;

	upt = find_export(g_mshell.export, new);
	if (upt)
	{
		if (choose == EQUAL)
			update_export_equal(new);
		else if (choose == VALUE)
			update_export_value(new);
	}
	else if (choose == VARIABLE)
		ex_add_back(&g_mshell.export, new_ex(ft_strdup_two(new, 12, VARIABLE)));
	else if (choose == EQUAL)
	{
		ex_add_back(&g_mshell.export, new_ex(ft_strdup_two(new, 14, EQUAL)));
		env_add_back(&g_mshell.env, new_env(ft_strdup(new)));
	}
	else if (choose == VALUE)
	{
		ex_add_back(&g_mshell.export, new_ex(ft_strjoin_two(new)));
		env_add_back(&g_mshell.env, new_env(ft_strdup(new)));
	}
}

int	ex_ctrl(char *cpy_exe, int choose)
{
	int	error;

	error = 0;
	if (choose == ERROR)
		error++;
	else if (choose == VARIABLE)
		new_value_export(cpy_exe, VARIABLE);
	else if (choose == EQUAL)
		new_value_export(cpy_exe, EQUAL);
	else if (choose == VALUE)
		new_value_export(cpy_exe, VALUE);
	return (error);
}

int	b_export(char **exe)
{
	int		i;
	int		choose;
	int		error;
	char	**cpy_exe;

	cpy_exe = exe;
	error = 0;
	if (count_value(exe) == 1)
		show_export();
	else
	{
		i = 1;
		while (cpy_exe[i])
		{
			choose = export_control(cpy_exe[i]);
			error += ex_ctrl(cpy_exe[i], choose);
			i++;
		}
	}
	if (error > 0)
		printf("minishell: export: '%s': not a valid identifier\n", cpy_exe[1]);
	return (0);
}
