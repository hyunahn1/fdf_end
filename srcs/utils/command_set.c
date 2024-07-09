/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:32:57 by hyunahn           #+#    #+#             */
/*   Updated: 2024/07/04 18:59:12 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_color_scheme(t_three_coordi_node *current, int base_color1,
		int base_color2, int base_color3)
{
	if (current->z >= 10)
		current->color = base_color1 + (current->z * 10);
	else if (current->z > 0 && current->z < 10)
		current->color = base_color2;
	else
		current->color = base_color3 + (current->z * 2);
}

void	change_colors(t_program *main)
{
	t_three_coordi_node	*current;

	current = main->map.nodes;
	while (current)
	{
		if (main->color_scheme == 0)
			apply_color_scheme(current, 0x00ff00, 0x0000ff, 0xff00ff);
		else if (main->color_scheme == 1)
			apply_color_scheme(current, 0xffa500, 0xff8c00, 0xdc143c);
		else if (main->color_scheme == 2)
			apply_color_scheme(current, 0x8a2be2, 0x5f9ea0, 0x7fff00);
		else if (main->color_scheme == 3)
			apply_color_scheme(current, 0xffff00, 0xff1493, 0x00fa9a);
		else if (main->color_scheme == 4)
			apply_color_scheme(current, 0x1e90ff, 0x20b2aa, 0x778899);
		else if (main->color_scheme == 5)
			apply_color_scheme(current, 0xd2691e, 0xff7f50, 0x8b4513);
		else if (main->color_scheme == 6)
			apply_color_scheme(current, 0x006400, 0x8fbc8f, 0x2f4f4f);
		current = current->next;
	}
	main->color_scheme = (main->color_scheme + 1) % 7;
}

void	handle_movement(int keycode, t_program *main)
{
	if (keycode == 65361)
		main->offset.x_offset -= 10;
	else if (keycode == 65363)
		main->offset.x_offset += 10;
	else if (keycode == 65362)
		main->offset.y_offset -= 10;
	else if (keycode == 65364)
		main->offset.y_offset += 10;
}

void	handle_reset_and_colors(int keycode, t_program *main)
{
	if (keycode == 32)
	{
		mlx_clear_window(main->mlx, main->win);
		reset_map(main);
		main->offset.angle = 0;
		main->offset.z_scale = 1;
		main->offset.is_orthographic = 1;
	}
	else if (keycode == 65513)
	{
		mlx_clear_window(main->mlx, main->win);
		main->offset.angle = 0.523599;
		main->offset.z_scale = 0.5;
		main->offset.is_orthographic = 0;
	}
	else if (keycode == 65289)
	{
		change_colors(main);
	}
}

int	ft_key_handling(int keycode, t_program *main)
{
	if (keycode == 65307)
	{
		ft_free(main->map.nodes);
		mlx_destroy_image(main->mlx, main->img.img);
		mlx_destroy_window(main->mlx, main->win);
		mlx_destroy_display(main->mlx);
		free(main->mlx);
		exit(0);
	}
	else if (keycode == 65507)
		adjust_map(main, 1.1, 1.1);
	else if (keycode == 65508)
		adjust_map(main, 0.9, 0.9);
	else if (keycode == 65471)
		rotate_y(main, 7);
	else if (keycode == 'z')
		adjust_z_scale(main, 0.9);
	else if (keycode == 'x')
		adjust_z_scale(main, 1.1);
	else
		handle_movement(keycode, main);
	handle_reset_and_colors(keycode, main);
	render(main);
	return (0);
}
