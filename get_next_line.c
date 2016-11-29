/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouanik <mbouanik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 03:08:36 by mbouanik          #+#    #+#             */
/*   Updated: 2016/11/29 13:35:10 by mbouanik         ###   ########.fr       */
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

void				ft_lst_get_del(t_fd *index, t_fd **alst)
{
	t_fd *tmp;

	tmp = NULL;
	if (index->next == NULL)
	{
		free(*alst);
		*alst = NULL;
	}
	tmp = index;
	while ((*alst)->next != tmp)
		*alst = (*alst)->next;
	(*alst)->next = tmp->next;
	tmp = NULL;
	free(tmp);
}

int					get_next_line(const int fd, char **line)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	char			*tmp2;
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
	if (get_next->remain != NULL && ft_is_present(get_next->remain, '\n'))
	{
		tmp = get_next->remain;
		*line = ft_strdup_until(get_next->remain, '\n');
		get_next->remain = ft_strdup_after(get_next->remain, '\n');
		ft_strdel(&tmp);
		get_next = index;
		return (1);
	}
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		if (ft_is_present(buf, '\n'))
		{
			if (get_next->remain == NULL)
				*line = ft_strdup_until(buf, '\n');
			else
			{
				tmp = get_next->remain;
				tmp2 = ft_strdup_until(buf, '\n');
				*line = ft_strjoin(get_next->remain, tmp2);
				ft_strdel(&tmp2);
				ft_strdel(&tmp);
			}
			get_next->remain = ft_strdup_after(buf, '\n');
			get_next = index;
			return (1);
		}
		if (get_next->remain == NULL)
			get_next->remain = ft_strdup(buf);
		else
		{
			tmp = get_next->remain;
			get_next->remain = ft_strjoin(get_next->remain, buf);
			ft_strdel(&tmp);
		}
	}
	if (ret == 0 && get_next->remain != NULL && ft_strlen(get_next->remain))
	{
		*line = ft_strdup(get_next->remain);
		ft_strdel(&(get_next->remain));
		// ft_lst_get_del(index, &get_next);
		get_next = index;
		return (1);
	}
	ft_strdel(&(*line));
	return (0);
}
