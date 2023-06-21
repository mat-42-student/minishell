/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 19:27:12 by mdjemaa           #+#    #+#             */
/*   Updated: 2022/11/07 17:03:30 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	char	*str;

	last = 0;
	str = (char *) s;
	while (*str)
	{
		if (*str == (unsigned char)c)
			last = str;
		str++;
	}
	if ((unsigned char) c == '\0')
		return (str);
	return (last);
}
