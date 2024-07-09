/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:51:52 by hyunahn           #+#    #+#             */
/*   Updated: 2024/06/25 19:58:50 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free(t_three_coordi_node *points)
{
	t_three_coordi_node	*tmp;

	while (points)
	{
		tmp = points;
		points = points->next;
		free(tmp);
	}
}
