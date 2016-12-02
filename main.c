/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouanik <mbouanik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 01:03:08 by mbouanik          #+#    #+#             */
/*   Updated: 2016/11/30 11:08:11 by mbouanik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

int		main(int ac, char **av)
{
	char *str;
	int fd;
	int fd1;
	int fd2;

	ac = 1;
	fd = 0;
	fd1 = 0;
	fd2 = 0;
	fd = open(av[1],O_RDONLY);
	fd1 = open("test2",O_RDONLY);
	fd2 = open("test3",O_RDONLY);
	str = NULL;
	// get_next_line(fd, &str);
	// ft_putstr(str);
	// ft_putchar('\n');
	//
	// get_next_line(fd1, &str);
	// ft_putstr(str);
	// ft_putchar('\n');
	//
	// get_next_line(fd2, &str);
	// ft_putstr(str);
	// ft_putchar('\n');
	//
	// get_next_line(fd, &str);
	// ft_putstr(str);
	// ft_putchar('\n');
	//
	// get_next_line(fd1, &str);
	// ft_putstr(str);
	// ft_putchar('\n');
	//
	// get_next_line(fd2, &str);
	// ft_putstr(str);
	// ft_putchar('\n');

	while (get_next_line(fd, &str))
	{
		ft_putstr(str);
		ft_putchar('\n');
	}
	// while (get_next_line(fd1, &str))
	// {
	// 	ft_putstr(str);
	// 	ft_putchar('\n');
	// }
	// while (get_next_line(fd2, &str))
	// {
	// 	ft_putstr(str);
	// 	ft_putchar('\n');
	// }
	close(fd);
	close(fd1);
	close(fd2);
	return (0);
}
