/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:30:20 by hyunahn           #+#    #+#             */
/*   Updated: 2024/07/04 18:45:57 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->buffer + (y * img->line_bytes + x * (img->pixel_bits / 8));
	dst[0] = color & 0xFF;
	dst[1] = (color >> 8) & 0xFF;
	dst[2] = (color >> 16) & 0xFF;
	dst[3] = 0xFF;
}

void	init_draw_info(t_draw *draw_info, t_two_coordi_node p1,
		t_two_coordi_node p2)
{
	draw_info->dx = abs(p2.x - p1.x);
	draw_info->dy = abs(p2.y - p1.y);
	draw_info->err = draw_info->dx - draw_info->dy;
	if (p1.x < p2.x)
		draw_info->sx = 1;
	else
		draw_info->sx = -1;
	if (p1.y < p2.y)
		draw_info->sy = 1;
	else
		draw_info->sy = -1;
}

void	draw_line(t_two_coordi_node p1, t_two_coordi_node p2,
		t_program *main, int color)
{
	t_draw	draw_info;

	init_draw_info(&draw_info, p1, p2);
	while (1)
	{
		put_pixel_to_image(&main->img, p1.x + main->offset.x_offset,
			p1.y + main->offset.y_offset, color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		draw_info.e2 = draw_info.err * 2;
		if (draw_info.e2 > -draw_info.dy)
		{
			draw_info.err -= draw_info.dy;
			p1.x += draw_info.sx;
		}
		if (draw_info.e2 < draw_info.dx)
		{
			draw_info.err += draw_info.dx;
			p1.y += draw_info.sy;
		}
	}
}

void	draw_line_between_nodes(t_three_coordi_node *node1,
		t_three_coordi_node *node2, t_program *program)
{
	t_two_coordi_node	p1_iso;
	t_two_coordi_node	p2_iso;

	p1_iso = project_iso(*node1, program);
	p2_iso = project_iso(*node2, program);
	draw_line(p1_iso, p2_iso, program, node1->color);
}

void	draw_map(t_program *program)
{
	t_three_coordi_node	*current;
	t_three_coordi_node	*row_start;

	row_start = program->map.nodes;
	while (row_start)
	{
		current = row_start;
		while (current)
		{
			if (current->next && current->next->y == current->y)
				draw_line_between_nodes(current, current->next, program);
			if (current->y_next)
				draw_line_between_nodes(current, current->y_next, program);
			current = current->next;
		}
		row_start = row_start->y_next;
	}
}
