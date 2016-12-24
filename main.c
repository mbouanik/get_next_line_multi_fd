/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouanik <mbouanik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 21:57:02 by mbouanik          #+#    #+#             */
/*   Updated: 2016/12/22 22:04:22 by mbouanik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int main(int ac, char **av)
{
	int fd;
	char *line;

	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line))
		ft_putendl(line);
	return 0;
}
