/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:44:59 by makbas            #+#    #+#             */
/*   Updated: 2023/10/02 12:14:58 by rdemiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *str)
{
	char	*d;
	int		i;

	i = 0;
	d = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (d == NULL)
		return (0);
	while (str[i])
	{
		d[i] = str[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

void	add_declare_dup(char **dup)
{
	int		i;
	char	*dec;

	dec = "declare -x ";
	i = 0;
	while (dec[i])
	{
		(*dup)[i] = dec[i];
		i++;
	}
}

char	*ft_strdup_two(const char *str, int size, int choose)
{
	char	*d;
	int		i;
	int		j;

	d = ft_calloc((ft_strlen(str) + size), 1);
	if (d == NULL)
		return (0);
	add_declare_dup(&d);
	i = 0;
	j = 11;
	while (str[i])
	{
		d[j] = str[i];
		i++;
		j++;
	}
	if (choose == EQUAL)
	{
		d[j] = '\"';
		j++;
		d[j] = '\"';
	}
	return (d);
}
