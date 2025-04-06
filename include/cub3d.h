/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:19:21 by frromero          #+#    #+#             */
/*   Updated: 2025/04/06 17:27:40 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <X11/keysym.h>
#include <X11/X.h>

/* ERRORS */
#define SYNTAX_ERR "You must use this: ./cub3d <the_path/to/map.cub>"
#define OPEN_FILE_ERR "Map File error"
#define MALLOC_ERR "Map File error"
#define MAP_FORMAT "Invalid map format"

/* STRUCTURES */

typedef struct s_sprites
{
	void *no;
	void *su;
	void *we;
	void *ea;
} t_sprites;
typedef struct s_map
{
	char **raw_map;
	int raw_map_height;
	int map_height;
	char **map;
	// int width;
	// int height;
	// int player_x;
	// int player_y;
	t_sprites sprites;

} t_map;

typedef struct s_game
{
	t_map map;
	void *mlx;
	void *window;
	// int game_over;
} t_game;

int report_err(char *str);
int parse_arg(char *arg, t_game *data);
int load_map(char *arg, t_game *data);
void free_function(t_game *data);
void print_map_grid(char **grid, int height);
int open_file(char *arg);
#endif
