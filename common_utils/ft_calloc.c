/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:51:06 by hyunahn           #+#    #+#             */
/*   Updated: 2024/03/22 18:31:37 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_utils.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*src;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((nmemb * size) / nmemb != size)
		return (0);
	src = malloc(size * nmemb);
	if (!(src))
		return (0);
	ft_bzero(src, (size * nmemb));
	return (src);
}
