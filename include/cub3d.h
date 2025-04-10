/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:19:21 by frromero          #+#    #+#             */
/*   Updated: 2025/04/10 23:25:25 by user             ###   ########.fr       */
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

/* CONSTANTS */
#define FOV_COEF 0.66
#define MOVE_SPEED 0.05

// MOVEMENT
# define KEY_W         119 // 'w'
# define KEY_A         97  // 'a'
# define KEY_S         115 // 's'
# define KEY_D         100 // 'd'
# define KEY_ESC       65307 // ESC
# define KEY_LEFT      65361 // LEFT
# define KEY_RIGHT     65363 // RIGHT

/* ERRORS */
#define SYNTAX_ERR "You must use this: ./cub3d <the_path/to/map.cub>"
#define OPEN_FILE_ERR "Map File error"
#define MALLOC_ERR "Malloc error"
#define MAP_FORMAT "Invalid map format"
#define MAP_VOID "Invalid (void) map format"
#define ORIENTATION "Invalid orientation format (valid: NO textures/wall_1.xpm)"
#define TEXTURE_FILE "The texture file does not exist or is not accessible"
#define FORMAT_COLOR "Invalid color format (valid example: C 255,128,0)"
#define MAP_ITENS "Invalid (ITEMS) map format"
#define MAP_NOT_PLAYABLE "Map in not playable"

/* STRUCTURES */

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
	double x;
	double y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
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
	// int game_over;
} t_game;

// Functions

int report_err(char *str);
void parse_arg(char *arg, t_game *data);
void load_file(char *arg, t_game *data);
void free_function(t_game *data);
void print_map_grid(char **grid, int height);
int open_file(char *arg, t_game *data);
void parse_orientation(t_game *data);
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
// INIT GAME AND KEYS
void	init_player(t_game *data);
void	init_player_vectors(t_game *p);
int		key_press(int keycode, t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	game_loop(t_game *game);
int		exit_game(t_game *game);
void	window_init(t_game *game, int width, int height);
void	rotate_view(t_game *g, double angle);

// debugguer/testing
void testing(t_game *data);
#endif
