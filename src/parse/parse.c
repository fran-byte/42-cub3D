/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 23:43:36 by frromero          #+#    #+#             */
/*   Updated: 2025/04/05 11:57:53 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int open_file(char *arg)
{
	int fd;

	fd = open(arg, O_RDONLY);
	if (fd < 0)
	{
		report_err(OPEN_FILE_ERR);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int parse_arg(char *arg, t_game *data)
{
	int ln;
	int fd;
	
	ln = ft_strlen(arg);
	if (!(arg[ln - 1] == 'b' && arg[ln - 2] == 'u' && arg[ln - 3] == 'c' && arg[ln - 4] == '.'))
		return (report_err(SYNTAX_ERR), 1);
	load_map(arg, data);
	return (fd);
}
