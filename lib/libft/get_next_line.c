/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abytko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:32:58 by abytko            #+#    #+#             */
/*   Updated: 2018/09/28 14:05:39 by abytko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_charline(char **l, char *buff, int *ret)
{
	int		i;
	char	*temp;
	char	*str;

	i = 0;
	temp = NULL;
	while (buff[i] && (*ret)--)
	{
		if (buff[i] == '\n')
		{
			str = *l;
			temp = ft_strsub(buff, 0, i);
			*l = ft_strjoin(str, temp);
			free(temp);
			free(str);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	ft_remainder(t_list *list, char **l)
{
	size_t	i;
	char	*str;
	char	*temp;
	char	*s;

	i = 0;
	if ((str = list->content) == NULL)
		return (0);
	while (str[i])
	{
		if (str[i++] == '\n')
		{
			s = *l;
			temp = ft_strsub(list->content, 0, i - 1);
			*l = ft_strjoin(s, temp);
			free(s);
			free(temp);
			list->content = ft_strsub(str, i, ft_strlen(list->content) - i);
			free(str);
			return (1);
		}
	}
	return (0);
}

t_list		*ft_chooselist(t_list **list, const int fd)
{
	t_list	*temp;
	char	*str;

	temp = *list;
	while (temp)
	{
		if (temp->content_size == (size_t)fd)
		{
			return (temp);
		}
		temp = temp->next;
	}
	if (!(str = ft_strnew(fd)))
		return (NULL);
	temp = ft_lstnew(str, fd);
	ft_lstadd(list, temp);
	free(str);
	return (temp);
}

int			ft_read(const int fd, char **line, t_list **temp)
{
	int		ret;
	char	buff[BUFF_SIZE + 1];
	char	*temp_line;
	char	*str;

	while ((ret = read(fd, (void *)buff, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buff[ret] = '\0';
		if (ft_charline(line, buff, &ret))
		{
			(*temp)->content = ft_strsub(buff, ft_strlen(buff) - ret, ret);
			break ;
		}
		str = ft_strsub(buff, 0, ft_strlen(buff));
		temp_line = *line;
		if (!(*line = ft_strjoin(*line, str)))
			return (-1);
		free(str);
		free(temp_line);
	}
	if (ret == 0 && *line[0] == '\0' && buff[0] != '\n')
		return (0);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*list = NULL;
	t_list			*temp;
	char			*str;

	if (fd < 0 || !line)
		return (-1);
	if (!(temp = ft_chooselist(&list, fd)))
		return (-1);
	if (!(*line = ft_strnew(0)))
		return (-1);
	if (!ft_remainder(temp, line) && temp->content)
	{
		str = *line;
		if (!(*line = ft_strjoin(*line, temp->content)))
			return (-1);
		free(temp->content);
		free(str);
		temp->content = NULL;
	}
	if (temp->content)
		return (1);
	return (ft_read(fd, line, &temp));
}
