/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:54:44 by frromero          #+#    #+#             */
/*   Updated: 2025/05/20 20:51:00 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Retrieves the pixel data of the texture corresponding to the wall
 * direction.
 *
 * Selects the appropriate texture based on the given wall orientation and
 * returns a pointer to its pixel data. Also updates the texture width.
 *
 * @param g Pointer to the main game structure.
 * @param wall_dir The orientation of the wall (NORTH, SOUTH, EAST, WEST).
 * @param tex_width Pointer to an integer to store the texture width.
 * @return Pointer to the texture pixel data (array of colors).
 */
static int	*get_texture_pixels(t_game *g, t_orientation wall_dir,
		int *tex_width)
{
	void	*texture;
	int		*tex_;

	if (wall_dir == NORTH)
		texture = g->map.sprites.no;
	else if (wall_dir == SOUTH)
		texture = g->map.sprites.su;
	else if (wall_dir == EAST)
		texture = g->map.sprites.ea;
	else
		texture = g->map.sprites.we;
	tex_ = (int *)mlx_get_data_addr(texture, &g->img.bpp, tex_width,
			&g->img.endian);
	*tex_width /= 4;
	return (tex_);
}

/**
 * @brief Renders a textured vertical wall slice at a given screen position.
 *
 * Draws a vertical column of pixels on the screen representing the wall,
 * applying texture mapping based on the raycasting results.
 *
 * @param g Pointer to the main game structure.
 * @param x Horizontal screen coordinate where the wall column will be rendered.
 * @param ray Pointer to the raycasting information for the current ray.
 */
void	render_wall(t_game *g, int x, t_ray_info *ray)
{
	int			tex_y;
	int			color;
	int			pixel;
	t_wall_info	w;

	w.x = x;
	w.texture = get_texture_pixels(g, ray->wall_dir, &w.tex_width);
	w.tex_x = ray->tex_x;
	w.step = (double)w.tex_width / ray->wall_height;
	w.tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->wall_height / 2)
		* w.step;
	w.y = ray->draw_start;
	while (w.y < ray->draw_end)
	{
		tex_y = (int)w.tex_pos & (w.tex_width - 1);
		w.tex_pos += w.step;
		color = w.texture[tex_y * w.tex_width + w.tex_x];
		pixel = (w.y * g->img.line_len) + (w.x * (g->img.bpp / 8));
		*(int *)(g->img.addr + pixel) = color;
		w.y++;
	}
}
