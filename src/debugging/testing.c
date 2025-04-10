/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:38:30 by frromero          #+#    #+#             */
/*   Updated: 2025/04/10 16:44:38 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void testing(t_game *data)
{
	print_map_grid(data->map.file, data->map.height_file); // Fichero completo
	print_map_grid(data->map.map, data->map.height_map);   // Solo mapa
	printf("\n\nPATHs Almacenados:\nN: %s\nS: %s\nE: %s\nW: %s\n\n", data->map.paths.north, data->map.paths.south, data->map.paths.east, data->map.paths.west);
	printf("PLAYER INICIAL \n(Almacenamos con +0.5 para evitar problemas de colisiones)\nen: x: %f, y: %f\n\n", data->player.player_x, data->player.player_y);
}
