/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouanik <mbouanik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 03:11:14 by mbouanik          #+#    #+#             */
/*   Updated: 2016/12/02 15:16:10 by mbouanik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 500
# include "libft/libft.h"

typedef struct		s_fd
{
	int					fd;
	char				*remain;
	struct s_fd			*next;
}					t_fd;

int					get_next_line(const int fd, char **line);

#endif
