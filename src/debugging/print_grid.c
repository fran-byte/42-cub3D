/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:38:02 by frromero          #+#    #+#             */
/*   Updated: 2025/04/08 19:44:06 by frromero         ###   ########.fr       */
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

	i = 0;

	if (!grid || height <= 0)
	{
		printf("Error: Invalid map grid\n");
		return;
	}
	printf("\n=========== DEBUGGUER ==============");
	printf("\n======== FILE or MAP  ==============\n\n");
	while (i < height)
	{
		if (grid[i])
			printf("%s\n", grid[i]);
		else
			printf("(null)\n");
		i++;
	}
	printf("\n====================================\n\n");
}
