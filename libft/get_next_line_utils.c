/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:41:41 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:26:22 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/get_next_line.h"

int	where_is_nl(char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '\n')
			return (i);
	}
	return (-1);
}

int	gnl_init(size_t *i, size_t *j, char **line)
{
	*i = -1;
	*j = -1;
	if (!*line)
	{
		*line = malloc(1);
		if (!*line)
		{
			gnl_free(line, NULL);
			return (0);
		}
		*line[0] = 0;
	}
	return (1);
}

char	*gnl_cat(char **line, char *buf)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	if (!gnl_init(&i, &j, line))
		return (NULL);
	tmp = (char *) malloc(ft_sstrlen(*line) + ft_sstrlen(buf) + 1);
	if (!tmp)
		return (gnl_free(line, NULL));
	while ((*line)[++i])
		tmp[i] = (*line)[i];
	while (buf[++j])
		tmp[i + j] = buf[j];
	tmp[i + j] = 0;
	free(*line);
	i = 0;
	*line = tmp;
	return (*line);
}

char	*gnl_line(char **line, int pos)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = -1;
	ret = (char *) malloc(pos + 2);
	if (!ret)
		return (gnl_free(line, NULL));
	while (++i <= pos)
		ret[i] = (*line)[i];
	ret[i] = 0;
	tmp = (char *) malloc(ft_sstrlen(*line) - pos);
	if (!tmp)
		return (gnl_free(line, ret));
	i = 0;
	while ((*line)[i + pos + 1])
	{
		tmp[i] = (*line)[i + pos + 1];
		i++;
	}
	tmp[i] = 0;
	free(*line);
	*line = tmp;
	return (ret);
}
