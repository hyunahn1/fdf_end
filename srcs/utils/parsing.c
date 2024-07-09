/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:14:59 by hyunahn           #+#    #+#             */
/*   Updated: 2024/07/04 18:36:39 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_three_coordi_node	*create_node(int x, int y, int z)
{
	t_three_coordi_node	*new_node;

	new_node = (t_three_coordi_node *)malloc(sizeof(t_three_coordi_node));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->x = x;
	new_node->y = y;
	new_node->z = z;
	if (z >= 10)
		new_node->color = 0xffa500 + (z * 10);
	else if (z > 0 && z < 10)
		new_node->color = 0xff8c00;
	else
		new_node->color = 0xdc143c + (z * 2);
	new_node->next = NULL;
	new_node->y_next = NULL;
	return (new_node);
}

static char	**read_and_split_lines(int fd)
{
	char	*line;
	char	**values;

	line = get_next_line(fd);
	if (line)
	{
		values = ft_split(line, ' ');
		free(line);
	}
	else
		values = NULL;
	return (values);
}

static void	process_single_value(char *value, t_map *map,
		t_node_pointers *node_pointers, int cur_width)
{
	t_three_coordi_node	*new_node;
	int					z;

	z = ft_atoi(value);
	new_node = create_node(cur_width, map->cur_height, z);
	if (!map->nodes)
	{
		map->nodes = new_node;
		*(node_pointers->current_node) = new_node;
	}
	else
	{
		(*(node_pointers->current_node))->next = new_node;
		*(node_pointers->current_node) = new_node;
	}
	if (node_pointers->prev_line_nodes && \
		node_pointers->prev_line_nodes[cur_width - 1])
		node_pointers->prev_line_nodes[cur_width - 1]->y_next = new_node;
	if (map->cur_height == 1 || cur_width <= map->prev_width)
		node_pointers->prev_line_nodes[cur_width - 1] = new_node;
}

static void	process_line_to_nodes(char **values, t_map *map,
		t_three_coordi_node **current_node,
		t_three_coordi_node **prev_line_nodes)
{
	t_node_pointers		node_pointers;
	int					cur_width;
	int					i;

	node_pointers.current_node = current_node;
	node_pointers.prev_line_nodes = prev_line_nodes;
	i = 0;
	cur_width = 0;
	while (values[i])
	{
		process_single_value(values[i], map, &node_pointers, ++cur_width);
		i++;
	}
	if (map->prev_width != -1 && cur_width != map->prev_width)
	{
		ft_putendl_fd("ERROR: The file does not form a rectangle.", 1);
		exit(EXIT_FAILURE);
	}
	map->prev_width = cur_width;
	i = 0;
	while (values[i])
		free(values[i++]);
	free(values);
}

void	parsing_the_program(char *file, t_map *map)
{
	t_three_coordi_node	*current_node;
	t_three_coordi_node	**prev_line_nodes;
	int					fd;
	char				**values;

	map->cur_height = 1;
	map->prev_width = -1;
	current_node = NULL;
	map->nodes = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	prev_line_nodes = (t_three_coordi_node **)malloc
		(sizeof(t_three_coordi_node *) * 1000);
	values = read_and_split_lines(fd);
	while (values)
	{
		process_line_to_nodes(values, map, &current_node, prev_line_nodes);
		map->cur_height++;
		values = read_and_split_lines(fd);
	}
	close(fd);
	map->width = map->prev_width;
	map->height = (--map->cur_height);
	free(prev_line_nodes);
}
