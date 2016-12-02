/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouanik <mbouanik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 03:08:36 by mbouanik          #+#    #+#             */
/*   Updated: 2016/12/02 15:01:21 by mbouanik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_fd			*ft_get_new_fd(t_fd **get_next, int fd)
{
	t_fd *get;

	get = (t_fd *)malloc(sizeof(t_fd));
	get->fd = fd;
	get->remain = NULL;
	if (*get_next == NULL)
		get->next = get;
	else
	{
		get->next = (*get_next)->next;
		(*get_next)->next = get;
	}
	return (get);
}

static int		ft_assign(t_fd **get, char *buf, char **line)
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

int		ft_remain(t_fd **get, char **line)
{
	char	*tmp;

	if ((*get)->remain != NULL && ft_is_present((*get)->remain, '\n'))
	{
		tmp = (*get)->remain;
		*line = ft_strdup_until((*get)->remain, '\n');
		(*get)->remain = ft_strdup_after((*get)->remain, '\n');
		ft_strdel(&tmp);
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
		get_next = ft_get_new_fd(&get_next, fd);
	index = get_next;
	index = index->next;
	while (index != get_next)
	{
		if (index->fd == fd)
		{
			get_next = index;
			break ;
		}
		index = index->next;
	}
	if (index->fd != fd)
		get_next = ft_get_new_fd(&get_next, fd);
	if (get_next->fd < 0)
		return (-1);
	if (ft_remain(&get_next, &(*line)))
		return (1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		if (ft_assign(&get_next, buf, &(*line)))
			return (1);
	}
	if (ret == 0 && get_next->remain != NULL && ft_strlen(get_next->remain))
	{
		*line = ft_strdup(get_next->remain);
		ft_strdel(&(get_next->remain));
		return (1);
	}
	ft_strdel(&(*line));
	return (0);
}
