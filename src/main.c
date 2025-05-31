/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:17:52 by frromero          #+#    #+#             */
/*   Updated: 2025/05/31 18:10:10 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Loads and displays the introductory screen image.
 *
 * This function loads an XPM image from the specified path, initializes
 * the intro screen structure, and displays it on the window. If the image
 * fails to load, it reports an error and exits the program.
 *
 * @param g Pointer to the main game structure containing MLX pointers
 * and intro screen data.
 */
void	load_intro_screen(t_game *g)
{
	int	tex_w;
	int	tex_h;

	tex_w = 0;
	tex_h = 0;
	store_path(g, "   textures/intro.xpm", &g->map.paths.intro);
	g->intro.img = mlx_xpm_file_to_image(g->mlx, g->map.paths.intro, &tex_w,
			&tex_h);
	if (!g->intro.img)
	{
		report_err(TEXTURE_LOADING_ERROR);
		free_function(g);
		exit(EXIT_FAILURE);
	}
	g->intro.data = (int *)mlx_get_data_addr(g->intro.img, &g->img.bpp,
			&g->img.line_len, &g->img.endian);
	g->intro.width = SCREEN_WIDTH;
	g->intro.height = SCREEN_HEIGHT;
	g->intro.active = true;
	mlx_put_image_to_window(g->mlx, g->window, g->intro.img, 0, 0);
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
