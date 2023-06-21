/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:18:11 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:25:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (lst && *lst && del)
	{
		if ((*lst)->next)
			ft_lstclear(&(*lst)->next, del);
		del((*lst)->content);
		free(*lst);
		*lst = NULL;
	}
}
