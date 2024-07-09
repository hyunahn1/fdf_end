/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:10:37 by hyunahn           #+#    #+#             */
/*   Updated: 2024/07/04 18:27:35 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	reset_map(t_program *main)
{
	t_three_coordi_node	*current;

	current = main->map.nodes;
	while (current)
	{
		current->x = current->initial_x;
		current->y = current->initial_y;
		current->z = current->initial_z;
		current = current->next;
	}
}

int	ft_exit_handling(void *param)
{
	t_program	*main;

	main = (t_program *)param;
	ft_free(main->map.nodes);
	mlx_destroy_image(main->mlx, main->img.img);
	mlx_destroy_window(main->mlx, main->win);
	mlx_destroy_display(main->mlx);
	free(main->mlx);
	exit (0);
	return (0);
}

void	adjust_z_scale(t_program *main, float scale_factor)
{
	main->offset.z_scale *= scale_factor;
}

void	rotate_y(t_program *p, double angle)
{
	t_three_coordi_node	*current;
	double				rad;
	double				pi;
	double				x;
	double				z;

	current = p->map.nodes;
	pi = 3.14159265359;
	rad = angle * (pi / 180);
	{
		while (current)
		{
			x = current->x * cos(rad) + current->z * sin(rad);
			z = -current->x * sin(rad) + current->z * cos(rad);
			current->x = x;
			current->z = z;
			current = current->next;
		}
	}
}

void	adjust_map(t_program *main, double scale, double z_scale)
{
	t_three_coordi_node	*current;

	current = main->map.nodes;
	while (current)
	{
		current->x *= scale;
		current->y *= scale;
		current->z *= z_scale;
		current = current->next;
	}
}
