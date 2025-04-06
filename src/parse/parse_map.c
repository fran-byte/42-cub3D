/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:28:38 by frromero          #+#    #+#             */
/*   Updated: 2025/04/05 11:36:30 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void fill_raw_map_grid(char *arg, t_game *data)
{
    char **grid;
    char *line;
    int i;
	int fd;

	fd = open_file(arg);
	i = 0;
	grid = data->map.raw_map;
    line = get_next_line(fd);
    while (line != NULL)
    {
        grid[i] = malloc(ft_strlen(line) + 1);	
        if (!grid[i])
        {
            report_err(MALLOC_ERR);
            close(fd);
            free_function(data);
            return;
        }

        ft_strlcpy(grid[i], line, ft_strlen(line) + 1);
        free(line);
        i++;
        line = get_next_line(fd);
    }
    close(fd);
}
void get_map_height(int fd, t_game *data)
{
    int height;
    char *line;

	height = 0;
    line = get_next_line(fd); 
    while (line != NULL)
    {
        height++;		
        free(line);
        line = get_next_line(fd);
    }
	data->map.raw_map_height = height;
	close (fd);  
}

int load_map(char *arg, t_game *data)
{

    int height;
	int fd;

	fd = open_file(arg);	
	get_map_height(fd, data);
	
	height = data->map.raw_map_height;
    char **grid = malloc(sizeof(char *) * height);

    if (!grid)
    {
        report_err(MALLOC_ERR);
        close(fd);
        free_function(data);
        return (-1);
    }

    data->map.raw_map = grid;

    fill_raw_map_grid(arg, data); 
    return (0);
}

