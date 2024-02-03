/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:09:31 by makbas            #+#    #+#             */
/*   Updated: 2023/10/02 12:15:03 by rdemiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		s;
	char	*join;

	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	s = 0;
	if (!join)
		return (0);
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[s] != '\0')
	{
		join[i] = s2[s];
		s++;
		i++;
	}
	join[i] = '\0';
	return (join);
}

void	add_declare_join(char **join)
{
	int		i;
	char	*dec;

	dec = "declare -x ";
	i = 0;
	while (dec[i])
	{
		(*join)[i] = dec[i];
		i++;
	}
}

char	*ft_strjoin_two(char const *s1)
{
	int		i;
	int		j;
	char	*join;

	join = ft_calloc((ft_strlen(s1) + 14), 1);
	i = 0;
	j = 11;
	if (!join)
		return (0);
	add_declare_join(&join);
	while (s1[i] != '\0')
	{
		if (s1[i] == '=')
		{
			join[j] = s1[i];
			j++;
			join[j] = '\"';
		}
		else
			join[j] = s1[i];
		j++;
		i++;
	}
	join[j] = '\"';
	return (join);
}
