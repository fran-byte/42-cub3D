/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:33:15 by frromero          #+#    #+#             */
/*   Updated: 2025/05/20 20:27:21 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Renders the floor from a given y-coordinate to the bottom of the
 * screen.
 *
 * Colors all pixels below a given horizontal line with the specified color.
 *
 * @param g Pointer to the game structure.
 * @param y_start Starting y-coordinate for floor rendering.
 * @param color Floor color in integer format.
 */
void	render_floor(t_game *g, int y_start, int color)
{
	int	x;
	int	y;
	int	pixel;

	y = y_start;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			pixel = (y * g->img.line_len) + (x * (g->img.bpp / 8));
			*(int *)(g->img.addr + pixel) = color;
			x++;
		}
		y++;
	}
}

/**
 * @brief Renders the ceiling from the top of the screen to a given
 * y-coordinate.
 *
 * Colors all pixels above a given horizontal line with the specified color.
 *
 * @param g Pointer to the game structure.
 * @param y_end Ending y-coordinate for ceiling rendering.
 * @param color Ceiling color in integer format.
 */
void	render_ceiling(t_game *g, int y_end, int color)
{
	int	x;
	int	y;
	int	pixel;

	y = 0;
	while (y < y_end)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			pixel = (y * g->img.line_len) + (x * (g->img.bpp / 8));
			*(int *)(g->img.addr + pixel) = color;
			x++;
		}
		y++;
	}
}

/**
 * @brief Renders a complete frame by casting rays and drawing the scene.
 *
 * Performs raycasting, renders the ceiling and floor, draws vertical wall
 * slices, and updates the image on the screen.
 *
 * @param g Pointer to the main game structure containing all rendering info.
 */
void	render_frame(t_game *g)
{
	int			x;
	t_ray_info	rays[SCREEN_WIDTH];

	x = 0;
	calculate_raycasting(g, rays);
	render_ceiling(g, SCREEN_HEIGHT / 2, g->map.ceiling_color);
	render_floor(g, SCREEN_HEIGHT / 2, g->map.floor_color);
	while (x < SCREEN_WIDTH)
	{
		render_wall(g, x, &rays[x]);
		x++;
	}
	mlx_put_image_to_window(g->mlx, g->window, g->img.img, 0, 0);
}
