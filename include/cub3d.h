/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:19:21 by frromero          #+#    #+#             */
/*   Updated: 2025/04/10 18:59:53 by frromero         ###   ########.fr       */
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
#define MALLOC_ERR "Malloc error"
#define MAP_FORMAT_ERR "Invalid map format"
#define ELEMENT_FORMAT_ERR "Invalid map format"
#define MISSING_ELEMENT_ERR "Invalid map format"
#define MAP_VOID_ERR "Invalid (void) map format"
#define ORIENTATION_FILE_ERR "Invalid Orinetation format (valid: NO textures/wall_1.xpm)"
#define TEXTURE_FILE_ERR "The texture file does not exist or is not accessible"
#define FORMAT_COLOR_ERR "Invalid color format (valid example: C 255,128,0)"
#define MAP_ITENS_ERR "Invalid (ITEMS) map format"
#define MAP_PLAYABLE_ERR "Map in not playable"

/* STRUCTURES */

typedef struct s_elem
{
	int north;
	int south;
	int west;
	int east;
	int floor;
	int ceiling;
} t_elem;

typedef struct s_sprites
{
	void *no;
	void *su;
	void *we;
	void *ea;
} t_sprites;

typedef enum e_orientation
{
	EAST,
	WEST,
	NORTH,
	SOUTH
} t_orientation;

typedef struct s_player
{
	double player_x;
	double player_y;
	t_orientation player_orinetation;
} t_player;

typedef struct s_paths // los paths del fichero
{
	char *north;
	char *south;
	char *west;
	char *east;
} t_paths;

typedef struct s_map
{
	int map_start_index;
	char **file;
	int height_file;
	char **map;
	int height_map;
	int celing_color;
	int floor_color;
	t_paths paths;
	t_sprites sprites;

} t_map;

typedef struct s_game
{
	t_map map;
	void *mlx;
	void *window;
	t_player player;
	t_elem elem;
	// int game_over;
} t_game;

// Functions

int report_err(char *str);
void parse_arg(char *arg, t_game *data);
void load_file(char *arg, t_game *data);
void free_function(t_game *data);
void print_map_grid(char **grid, int height);
int open_file(char *arg, t_game *data);
void parse_color_line(t_game *data, char *line);
void store_path(t_game *data, char *line, char **dest);
void parse_elements(t_game *data);
void free_split(char **grid_color);
void parse_colors(t_game *data);
int is_numeric(const char *str);
int count_char_in_str(const char *str, char c);
void parse_map(t_game *data);
int ft_array_size(char **array);
void parse_items_map(t_game *data);
void parse_validate_map(t_game *data);
void free_grid(char **grid, int height);
char **duplicate_grid(char **grid, int height);
int is_empty_line(char *line);

// debugguer/testing
void testing(t_game *data);
#endif
