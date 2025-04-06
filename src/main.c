/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:17:52 by frromero          #+#    #+#             */
/*   Updated: 2025/04/05 11:58:01 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(int argc, char **argv)
{
	t_map *map;
	t_game data;
	int fd;

	if (argc != 2)
		return (report_err(SYNTAX_ERR), 1);
	fd = parse_arg(argv[1], &data);
	//printf("DEBUGGUER >>>>>>");
	map = malloc(sizeof(t_map));
	 if (!map)
	 	report_err(MALLOC_ERR);
	print_map_grid(data.map.raw_map, data.map.raw_map_height);

	return (0);
}
