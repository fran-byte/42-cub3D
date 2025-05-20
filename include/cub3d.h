/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:19:21 by frromero          #+#    #+#             */
/*   Updated: 2025/05/20 20:37:10 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/******************************************************************************/
/*                                  INCLUDES                                  */
/******************************************************************************/

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

/******************************************************************************/
/*                                 CONSTANTS                                  */
/******************************************************************************/
# define FOV_COEF 0.66
# define MOVE_SPEED 0.05
# define TEX_WIDTH 512
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

/******************************************************************************/
/*                                 MOVEMENT                                   */
/******************************************************************************/
# define KEY_W 119       /* 'w' key for forward movement                  */
# define KEY_A 97        /* 'a' key for left movement                     */
# define KEY_S 115       /* 's' key for backward movement                 */
# define KEY_D 100       /* 'd' key for right movement                    */
# define KEY_ESC 65307   /* ESC key to exit game                          */
# define KEY_LEFT 65361  /* Left arrow key for rotate left                */
# define KEY_RIGHT 65363 /* Right arrow key for rotate right              */

/******************************************************************************/
/*                                  ERRORS                                    */
/******************************************************************************/
# define SYNTAX_ERR "You must use this: ./cub3d <the_path/to/map.cub>"
# define OPEN_FILE_ERR "Map File error"
# define MALLOC_ERR "Malloc error"
# define MAP_FORMAT_ERR "Invalid map format"
# define ELEMENT_FORMAT_ERR "Invalid map format"
# define MISSING_ELEMENT_ERR "Invalid map format (Missing Elements)"
# define MAP_VOID_ERR "Invalid map format (void)"
# define ORIENTATION_FILE_ERR "Invalid Orinetation format (valid: wall_1.xpm)"
# define TEXTURE_FILE_ERR "The texture file does not exist or is not accessible"
# define FORMAT_COLOR_ERR "Invalid color format (valid example: C 255,128,0)"
# define MAP_ITENS_ERR "Invalid map format (Items)"
# define MAP_PLAYABLE_ERR "Map in not playable"
# define MLX_INIT_ERR "mlx_init failed"
# define MLX_NEW_WINDOW_ERR "mlx_new_window failed"
# define MLX_OR_WINDOW_ERR "mlx or window not initialized"
# define TEXTURE_LOADING_ERROR "Texture loading Error"

/******************************************************************************/
/*                                STRUCTURES                                  */
/******************************************************************************/

/* ************************************************************************** */
/*            Special structure to store render_wall() variables              */
/* ************************************************************************** */
typedef struct s_wall_info
{
	int				x;
	int				tex_width;
	int				*texture;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				y;
}					t_wall_info;

/* ************************************************************************** */
/*                Structure to store wall orientation flags                   */
/* ************************************************************************** */
typedef struct s_elem
{
	int				north;
	int				south;
	int				west;
	int				east;
	int				floor;
	int				ceiling;
}					t_elem;

/* ************************************************************************** */
/*                   Structure to store loaded wall textures                  */
/* ************************************************************************** */
typedef struct s_sprites
{
	void			*no;
	void			*su;
	void			*we;
	void			*ea;
}					t_sprites;

/* ************************************************************************** */
/*                  Enum for cardinal directions (N/S/E/W)                    */
/* ************************************************************************** */
typedef enum e_orientation
{
	EAST,
	WEST,
	NORTH,
	SOUTH
}					t_orientation;

/* ************************************************************************** */
/*                Structure storing raycasting render data                    */
/* ************************************************************************** */
typedef struct s_ray_info
{
	double			distance;
	int				wall_height;
	int				draw_start;
	int				draw_end;
	int				tex_x;
	t_orientation	wall_dir;
}					t_ray_info;

/* ************************************************************************** */
/*                     MLX image data structure                               */
/* ************************************************************************** */
typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

/* ************************************************************************** */
/*                   Player position and direction data                       */
/* ************************************************************************** */
typedef struct s_player
{
	double			player_x;
	double			player_y;
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	t_orientation	player_orientation;
}					t_player;

/* ************************************************************************** */
/*                Paths to texture files (NO/SO/WE/EA)                        */
/* ************************************************************************** */
typedef struct s_paths
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
}					t_paths;

/* ************************************************************************** */
/*                      Complete map data structure                           */
/* ************************************************************************** */
typedef struct s_map
{
	int				map_start_index;
	char			**file;
	int				height_file;
	char			**map;
	int				height_map;
	int				ceiling_color;
	int				floor_color;
	t_paths			paths;
	t_sprites		sprites;
}					t_map;

/* ************************************************************************** */
/*                Temporary variables for raycasting math                     */
/* ************************************************************************** */
typedef struct s_ray_vars
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				side;
}					t_ray_vars;

/* ************************************************************************** */
/*                  Master game state structure                               */
/* ************************************************************************** */
typedef struct s_game
{
	t_map			map;
	void			*mlx;
	void			*window;
	t_player		player;
	t_elem			elem;
	t_img			img;
}					t_game;

/******************************************************************************/
/*                             FUNCTION PROTOTYPES                            */
/******************************************************************************/

/* ************************************************************************** */
/*                        Core game initialization                           */
/* ************************************************************************** */
void				init_game(t_game *game);
int					report_err(char *str);
void				parse_arg(char *arg, t_game *game);
void				load_file(char *arg, t_game *game);
void				free_function(t_game *game);

/* ************************************************************************** */
/*                          Map parsing utilities                            */
/* ************************************************************************** */
void				print_map_grid(char **grid, int height);
int					open_file(char *arg, t_game *game);
int					parse_color_line(t_game *game, char *line);
void				store_path(t_game *game, char *line, char **dest);
void				parse_elements(t_game *game);
void				free_split(char **grid_color);
void				parse_colors(t_game *game);
int					count_char_in_str(const char *str, char c);
void				parse_map(t_game *game);
int					ft_array_size(char **array);
void				parse_items_map(t_game *game);
void				parse_validate_map(t_game *game);
void				free_grid(char **grid, int height);
char				**duplicate_grid(char **grid, int height);
int					is_empty_line(char *line);

/* ************************************************************************** */
/*                          Rendering functions                              */
/* ************************************************************************** */
void				render_wall(t_game *g, int x, t_ray_info *ray);
void				calculate_raycasting(t_game *g, t_ray_info rays[]);
void				init_ray(t_game *g, int x, t_ray_vars *v);
void				perform_dda(t_game *g, t_ray_vars *v);
void				compute_wall_info(t_game *g, t_ray_info *ray,
						t_ray_vars *v);
void				compute_wall_orientation(t_ray_info *ray, t_ray_vars *v);
void				render_frame(t_game *g);
void				render_floor(t_game *g, int y_start, int color);
void				render_ceiling(t_game *g, int y_end, int color);

/* ************************************************************************** */
/*                          Texture management                               */
/* ************************************************************************** */
void				load_textures(t_game *g);
void				clean_exit(t_game *g, int exit_code);
bool				check_texture_sizes(int *w, int *h);

/* ************************************************************************** */
/*                      Player movement and controls                         */
/* ************************************************************************** */
void				init_player(t_game *game);
void				init_player_vectors(t_game *p);
int					key_press(int keycode, t_game *game);
void				move_forward(t_game *game);
void				move_backward(t_game *game);
void				move_left(t_game *game);
void				move_right(t_game *game);
void				game_loop(t_game *game);
int					exit_game(t_game *game);
void				window_init(t_game *game, int width, int height);
void				rotate_view(t_game *g, double angle);
#endif