/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:42:11 by hyunahn           #+#    #+#             */
/*   Updated: 2024/07/05 12:42:29 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_two_coordi_node	project_iso(t_three_coordi_node p, t_program *main)
{
	t_two_coordi_node	result;

	if (main->offset.is_orthographic)
	{
		p.z = 0;
		result.x = p.initial_x * main->offset.scale;
		result.y = p.initial_y * main->offset.scale;
	}
	else
	{
		result.x = (p.x * cos(main->offset.angle) - \
			p.y * cos(main->offset.angle)) * main->offset.scale;
		result.y = ((p.x * sin(main->offset.angle) + \
			p.y * sin(main->offset.angle)) - \
			(p.z * main->offset.z_scale)) * main->offset.scale;
	}
	return (result);
}
