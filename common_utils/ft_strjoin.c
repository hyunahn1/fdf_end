/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:17:46 by hyunahn           #+#    #+#             */
/*   Updated: 2024/03/15 17:32:47 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_utils.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*arr;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (0);
	arr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!arr)
		return (0);
	i = -1;
	j = 0;
	while (s1[++i])
		arr[i] = s1[i];
	while (s2[j])
		arr[i++] = s2[j++];
	arr[i] = '\0';
	free(s1);
	s1 = 0;
	return (arr);
}
