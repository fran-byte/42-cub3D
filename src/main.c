/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:17:52 by frromero          #+#    #+#             */
/*   Updated: 2025/06/01 20:36:17 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Constructs the file path for an intro frame image based on the frame
 * index.
 *
 * This function generates a string path of the form "textures/i/X.xpm" where X
 * is the frame number (1-based). It handles numbers less than 10 and those with
 * two digits.
 *
 * @param path  A buffer to store the resulting path string (must be at least 64
 * bytes).
 * @param index The zero-based index of the frame.
 */
void	get_intro_frame_path(char *path, int index)
{
	char	num[4];

	if (index + 1 < 10)
	{
		num[0] = '0' + (index + 1);
		num[1] = '\0';
	}
	else
	{
		num[0] = '0' + ((index + 1) / 10);
		num[1] = '0' + ((index + 1) % 10);
		num[2] = '\0';
	}
	ft_strlcpy(path, "textures/i/", 64);
	ft_strlcat(path, num, 64);
	ft_strlcat(path, ".xpm", 64);
}

/**
 * @brief Loads all intro screen frames into the game structure.
 *
 * This function initializes the intro screen state and loads each XPM image
 * frame into the game's intro frames array using MiniLibX. If any frame fails
 * to load, it reports an error, frees resources, and exits the program.
 *
 * @param g Pointer to the main game structure containing MLX pointers
 *          and intro screen data.
 */
void	load_intro_screen(t_game *g)
{
	int		i;
	int		w;
	int		h;
	char	path[64];

	i = 0;
	w = 0;
	h = 0;
	g->intro.current_frame = 0;
	g->intro.ticks = 0;
	g->intro.active = true;
	while (i < INTRO_FRAME_COUNT)
	{
		get_intro_frame_path(path, i);
		g->intro.frames[i] = mlx_xpm_file_to_image(g->mlx, path, &w, &h);
		if (g->intro.frames[i] == NULL)
		{
			report_err(TEXTURE_LOADING_ERROR);
			free_function(g);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

/**
 * @brief Entry point of the Cub3D program.
 *
 * Validates arguments, initializes the game, parses the map file,
 * sets up the player and rendering window, and starts the main loop.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Exit status (0 if success, 1 if error).
 */
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (report_err(SYNTAX_ERR), 1);
	init_game(&game);
	parse_arg(argv[1], &game);
	init_player(&game);
	window_init(&game, SCREEN_WIDTH, SCREEN_HEIGHT);
	load_intro_screen(&game);
	game_loop(&game);
	free_function(&game);
	return (0);
}
