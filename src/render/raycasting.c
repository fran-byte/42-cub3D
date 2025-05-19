/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:55:39 by user              #+#    #+#             */
/*   Updated: 2025/05/18 18:14:07 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
