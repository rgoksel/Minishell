/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:39:00 by makbas            #+#    #+#             */
/*   Updated: 2023/10/02 12:23:45 by rdemiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_lst_delone(char *str)
{
	t_env	*env_node;
	t_env	*temp;
	char	*env_str;

	env_node = g_mshell.env;
	if (!env_node)
		return ;
	while (env_node->next)
	{
		env_str = env_node->next->str;
		if (ft_strcmp_env(str, env_str))
		{
			temp = env_node->next;
			env_node->next = env_node->next->next;
			free(temp->str);
			free(temp);
			break ;
		}
		env_node = env_node->next;
	}
}

void	export_lst_delone(char *str)
{
	t_export	*export_node;
	t_export	*temp;
	char		*node_str;

	export_node = g_mshell.export;
	if (!export_node)
		return ;
	while (export_node->next)
	{
		node_str = export_node->next->str;
		if (ft_strcmp_ex(node_str, str))
		{
			temp = export_node->next;
			export_node->next = export_node->next->next;
			free(temp->str);
			free(temp);
			break ;
		}
		export_node = export_node->next;
	}
}

int	unset_control(char *str)
{
	int	i;
	int	len;
	int	equal_i;
	int	value;

	i = 0;
	len = ft_strlen(str);
	equal_i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			equal_i = i;
		i++;
	}
	value = -1;
	if ((str[0] >= '0' && str[0] <= '9') == 1)
		value = ERROR;
	else if (equal_i == 0)
		value = VARIABLE;
	else if (equal_i + 1 == len)
		value = EQUAL;
	else if (equal_i + 1 < len)
		value = VALUE;
	return (value);
}

void	b_unset2(char *exe)
{
	int	choose;
	int	error;

	error = 0;
	choose = unset_control(exe);
	if (choose == VARIABLE)
	{
		export_lst_delone(exe);
		env_lst_delone(exe);
	}
	else
	{
		error++;
		if (error > 0)
			printf("bash: unset: `%s': not a valid identifier\n", exe);
	}
}

int	b_unset(char **exe)
{
	int	i;
	int	error;

	error = 0;
	if (count_value(exe) >= 2)
	{
		i = 1;
		while (exe[i])
		{
			b_unset2(exe[i]);
			i++;
		}
	}
	return (0);
}
