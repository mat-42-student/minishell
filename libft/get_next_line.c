/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:41:35 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:26:24 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/get_next_line.h"

char	*gnl_eof(char **line)
{
	char	*tmp;

	if (*line && (*line)[0])
	{
		tmp = ft_strdup(*line);
		free(*line);
		*line = NULL;
		return (tmp);
	}
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	return (NULL);
}

char	*gnl_free(char **s1, char *s2)
{
	if (s2)
		free(s2);
	free(*s1);
	*s1 = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		buf[BUFFER_SIZE + 1];
	int			lu;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	while (1)
	{
		lu = where_is_nl(line);
		if (line && lu >= 0)
			return (gnl_line(&line, lu));
		lu = read(fd, (char *) buf, BUFFER_SIZE);
		if (lu == -1)
			return (gnl_free(&line, NULL));
		buf[lu] = 0;
		if (lu == 0)
			return (gnl_eof(&line));
		if (!gnl_cat(&line, buf))
			return (NULL);
	}
	return (NULL);
}
/*
int	main(void)
{
	int		fd;
	char	*ligne;

	fd = open("test", O_RDONLY);
	while ((ligne = get_next_line(fd)))
		printf("%s", ligne);
	close(fd);
//	printf("%d", BUFFER_SIZE);
	return (0);
}
*/