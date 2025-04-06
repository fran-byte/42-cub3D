/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:38:02 by frromero          #+#    #+#             */
/*   Updated: 2025/04/05 11:52:06 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
 * Prints the map grid with borders for better visualization
 * @param grid The 2D array containing the map
 * @param height The height (number of rows) of the map
 */
void print_map_grid(char **grid, int height)
{
	int i;

	if (!grid || height <= 0)
	{
		printf("Error: Invalid map grid\n");
		return;
	}
	printf("\n=========== DEBUGGUER ==========");
	printf("\n=== MAP GRID or MAP RAW GRID ===\n\n");
	for (i = 0; i < height; i++)
	{
		if (grid[i])
			printf("%s", grid[i]);
		else
			printf("(null)\n");
	}
	printf("\n===============\n\n");
}
