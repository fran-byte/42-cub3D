/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:36:13 by frromero          #+#    #+#             */
/*   Updated: 2024/12/22 20:41:47 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*special_strjoin_(char *stored, char *read_bff)
{
	int		total_sz;
	char	*str;

	if (!read_bff)
	{
		read_bff = malloc(sizeof(char) + 1);
		if (!read_bff)
			return (NULL);
		read_bff[0] = 0;
	}
	total_sz = ft_strlen(read_bff) + ft_strlen(stored);
	str = (char *)malloc((sizeof(char) * total_sz) + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, stored, total_sz + 1);
	ft_strlcat(str, read_bff, total_sz + 1);
	free(stored);
	return (str);
}
