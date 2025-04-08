/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:32:50 by frromero          #+#    #+#             */
/*   Updated: 2025/04/08 10:36:08 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int open_file(char *arg, t_game *data)
{
	int fd;

	fd = open(arg, O_RDONLY);
	if (fd < 0)
	{
		report_err(OPEN_FILE_ERR);
		free_function(data);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
void free_split(char **grid_color)
{
	int i;

	if (!grid_color)
		return;
	i = 0;
	while (grid_color[i])
	{
		free(grid_color[i]);
		i++;
	}
	free(grid_color);
}
