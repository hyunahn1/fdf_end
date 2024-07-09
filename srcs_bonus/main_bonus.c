/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:13:47 by hyunahn           #+#    #+#             */
/*   Updated: 2024/07/04 18:25:42 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*check_err_parse(int argc, char **argv, t_program *main)
{
	int	fd;

	if (argc == 1 || argc > 2)
	{
		ft_putendl_fd("ERROR: argv error.", 1);
		exit(EXIT_FAILURE);
	}
	if (main->mlx == 0)
	{
		ft_putendl_fd("ERROR: file error.", 1);
		exit(EXIT_FAILURE);
	}
	if (!ft_strrstr(argv[1], ".fdf", 4))
		ft_error("ERROR: WRONG FILE");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_error("ERROR: Could not read");
	close(fd);
	main->file = argv[1];
	return (argv[1]);
}

void	save_initial_coordinates(t_map *map)
{
	t_three_coordi_node	*current;

	current = map->nodes;
	while (current)
	{
		current->initial_x = current->x;
		current->initial_y = current->y;
		current->initial_z = current->z;
		current = current->next;
	}
}

int	render(t_program *program)
{
	void	*new_img;
	char	*new_buffer;

	new_img = mlx_new_image(program->mlx,
			program->img.width, program->img.height);
	new_buffer = mlx_get_data_addr(new_img, &program->img.pixel_bits,
			&program->img.line_bytes, &program->img.endian);
	program->img.buffer = new_buffer;
	draw_map(program);
	mlx_put_image_to_window(program->mlx, program->win, new_img, 0, 0);
	mlx_destroy_image(program->mlx, program->img.img);
	program->img.img = new_img;
	program->img.buffer = new_buffer;
	return (0);
}

void	init_fdf_program(t_program *main)
{
	main->width = 2000;
	main->height = 2000;
	main->img.width = main->width;
	main->img.height = main->height;
	main->offset.scale = 20;
	main->offset.x_offset = 300;
	main->offset.y_offset = 300;
	main->offset.z_scale = 0.1;
	main->offset.angle = 0.523599;
	main->offset.is_orthographic = 0;
}

int	main(int argc, char **argv)
{
	t_program	main;

	main.mlx = mlx_init();
	init_fdf_program(&main);
	mlx_get_screen_size(main.mlx, &main.width, &main.height);
	parsing_the_program(check_err_parse(argc, argv, &main), &main.map);
	save_initial_coordinates(&main.map);
	main.win = mlx_new_window (main.mlx, main.width, main.height, "LOVE");
	if (main.win == 0)
		exit(EXIT_FAILURE);
	main.img.img = mlx_new_image(main.mlx, main.img.width, main.img.height);
	if (main.img.img == 0)
		exit (EXIT_FAILURE);
	main.img.buffer = mlx_get_data_addr(main.img.img, &main.img.pixel_bits,
			&main.img.line_bytes, &main.img.endian);
	draw_map(&main);
	mlx_put_image_to_window(main.mlx, main.win, main.img.img, 0, 0);
	mlx_key_hook(main.win, ft_key_handling, &main);
	mlx_hook(main.win, 17, 0, ft_exit_handling, &main);
	mlx_loop_hook(main.mlx, render, &main);
	mlx_loop (main.mlx);
}
