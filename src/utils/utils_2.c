/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:16:50 by frromero          #+#    #+#             */
/*   Updated: 2025/04/09 17:32:43 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void free_grid(char **grid, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

char **duplicate_grid(char **grid, int height)
{
	char **new_grid;
	int i;

	i = 0;
	new_grid = malloc(sizeof(char *) * height);
	if (!new_grid)
		return (NULL);
	while (i < height)
	{
		new_grid[i] = ft_strdup(grid[i]);
		if (!new_grid[i])
		{
			while (i > 0)
				free(new_grid[--i]);
			free(new_grid);
			return (NULL);
		}
		i++;
	}
	return (new_grid);
}
