/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouanik <mbouanik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 03:08:36 by mbouanik          #+#    #+#             */
/*   Updated: 2016/11/30 10:10:47 by mbouanik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_fd			*ft_get_new_fd(int fd)
{
	t_fd *get;

	get = NULL;
	get = (t_fd *)malloc(sizeof(t_fd));
	get->remain = NULL;
	get->fd = fd;
	get->next = NULL;
	return (get);
}

static int		ft_assign(t_fd **get, char *buf, t_fd **index, char **line)
{
	char			*tmp;
	char			*tmp2;

	if (ft_is_present(buf, '\n'))
	{
		if ((*get)->remain == NULL)
			*line = ft_strdup_until(buf, '\n');
		else
		{
			tmp = (*get)->remain;
			tmp2 = ft_strdup_until(buf, '\n');
			*line = ft_strjoin((*get)->remain, tmp2);
			ft_strdel(&tmp2);
			ft_strdel(&tmp);
		}
		(*get)->remain = ft_strdup_after(buf, '\n');
		*get = *index;
		return (1);
	}
	if ((*get)->remain == NULL)
		(*get)->remain = ft_strdup(buf);
	else
	{
		tmp = (*get)->remain;
		(*get)->remain = ft_strjoin((*get)->remain, buf);
		ft_strdel(&tmp);
	}
	return (0);
}

int		ft_remain(t_fd **get, t_fd **index, char **line)
{
	char	*tmp;

	if ((*get)->remain != NULL && ft_is_present((*get)->remain, '\n'))
	{
		tmp = (*get)->remain;
		*line = ft_strdup_until((*get)->remain, '\n');
		(*get)->remain = ft_strdup_after((*get)->remain, '\n');
		ft_strdel(&tmp);
		*get = *index;
		return (1);
	}
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	static t_fd		*get_next = NULL;
	t_fd			*index;

	if (get_next == NULL)
		get_next = ft_get_new_fd(fd);
	index = get_next;
	while (get_next->next && get_next->fd != fd)
		get_next = get_next->next;
	if (get_next->next == NULL && get_next->fd != fd)
	{
		get_next->next = ft_get_new_fd(fd);
		get_next = get_next->next;
	}
	if (get_next->fd < 0)
		return (-1);
	if (ft_remain(&get_next, &index, &(*line)))
		return (1);

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		if (ft_assign(&get_next, buf, &index, &(*line)))
			return (1);
	}
	if (ret == 0 && get_next->remain != NULL && ft_strlen(get_next->remain))
	{
		*line = ft_strdup(get_next->remain);
		ft_strdel(&(get_next->remain));
		get_next = index;
		return (1);
	}
	ft_strdel(&(*line));
	return (0);
}
