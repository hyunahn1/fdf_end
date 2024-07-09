/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:12:10 by hyunahn           #+#    #+#             */
/*   Updated: 2024/06/18 15:44:15 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "../minilibx-linux/mlx.h"
# include "../common_utils/common_utils.h"

typedef struct s_draw
{
	double	dx;
	double	dy;
	double	sx;
	double	sy;
	double	err;
	double	e2;
}		t_draw;

typedef struct s_offset
{
	double	scale;
	double	x_offset;
	double	y_offset;
	double	z_scale;
	double	angle;
	int		is_orthographic;
}		t_offset;

typedef struct s_two_coordi_node
{
	int	x;
	int	y;
	int	color;

}		t_two_coordi_node;

typedef struct s_three_coordi_node
{
	struct s_three_coordi_node		*next;
	struct s_three_coordi_node		*y_next;
	double							x;
	double							y;
	double							z;
	double							initial_x;
	double							initial_y;
	double							initial_z;
	int								color;
}	t_three_coordi_node;

typedef struct s_img
{
	t_offset				offset;
	void					*img;
	int						pixel_bits;
	int						line_bytes;
	int						endian;
	int						width;
	int						height;
	char					*buffer;
}			t_img;

typedef struct s_map
{
	t_three_coordi_node	*nodes;
	int					width;
	int					height;
	int					cur_height;
	int					prev_width;
}		t_map;

typedef struct s_node_pointers
{
	t_three_coordi_node	**current_node;
	t_three_coordi_node	**prev_line_nodes;
}	t_node_pointers;

typedef struct s_program
{
	t_img					img;
	t_map					map;
	t_offset				offset;
	void					*mlx;
	void					*win;
	int						width;
	int						height;
	char					*file;
	double					zoom;
	int						color_scheme;
}		t_program;

t_two_coordi_node			project_iso(t_three_coordi_node p, t_program *main);
void						ft_putendl_fd(char *s, int fd);
char						*ft_strchr(const char *s, int c);
char						*ft_strjoin(char *s1, char *s2);
void						ft_error(char *arr);

char						*check_err_parse(int argc,
								char **argv, t_program *main);
void						save_initial_coordinates(t_map *map);
int							render(t_program *program);
void						init_fdf_program(t_program *main);

void						parsing_the_program(char *file, t_map *map);

void						ft_free(t_three_coordi_node *points);
void						ft_error(char *arr);

void						put_pixel_to_image(t_img *img, int x,
								int y, int color);
void						init_draw_info(t_draw *draw_info,
								t_two_coordi_node p1,
								t_two_coordi_node p2);
void						draw_line(t_two_coordi_node p1,
								t_two_coordi_node p2,
								t_program *main, int color);
void						draw_line_between_nodes(t_three_coordi_node *node1,
								t_three_coordi_node *node2, t_program *program);
void						draw_map(t_program *program);

void						apply_color_scheme(t_three_coordi_node *current,
								int base_color1,
								int base_color2, int base_color3);
void						change_colors(t_program *main);
void						handle_movement(int keycode, t_program *main);
void						handle_reset_and_colors(int keycode,
								t_program *main);
int							ft_key_handling(int keycode, t_program *main);

void						reset_map(t_program *main);
int							ft_exit_handling(void *param);
void						adjust_z_scale(t_program *main, float scale_factor);
void						rotate_y(t_program *p, double angle);
void						adjust_map(t_program *main,
								double scale, double z_scale);				
#endif
