/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:55:39 by user              #+#    #+#             */
/*   Updated: 2025/05/20 20:26:14 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Performs raycasting for each vertical stripe on screen
 *
 * Iterates over each screen column to cast a ray, perform DDA to detect walls,
 * calculate wall hit details, and determine wall orientation.
 *
 * @param g Game structure
 * @param rays Array to store raycasting results for each column
 */
void calculate_raycasting(t_game *g, t_ray_info rays[])
{
    int x;
    t_ray_vars v;

    x = 0;
    while (x < SCREEN_WIDTH)
    {
        init_ray(g, x, &v);
        perform_dda(g, &v);
        compute_wall_info(g, &rays[x], &v);
        compute_wall_orientation(&rays[x], &v);
        x++;
    }
}
