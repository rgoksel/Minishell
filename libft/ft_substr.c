/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:44:59 by makbas            #+#    #+#             */
/*   Updated: 2023/10/02 12:15:17 by rdemiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	bt;
	char	*str;

	if (s == NULL)
		return (0);
	if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	bt = 0;
	while ((bt < len) && (s[bt + start] != '\0'))
		bt++;
	str = (char *)malloc((sizeof(char) * bt) + 1);
	if (str == NULL)
		return (0);
	while (i < bt)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
