/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:29:00 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:25:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

t_2list	*ft_2lstnew(int value, int rank)
{
	t_2list	*new;

	new = (t_2list *) malloc (sizeof (t_2list));
	if (!new)
		return (0);
	new->val = value;
	new->rank = rank;
	new->next = new;
	new->prev = new;
	return (new);
}

void	ft_2lstadd_back(t_2list **lst, t_2list *new)
{
	if (lst)
	{
		if (*lst)
		{
			new->next = *lst;
			new->prev = (*lst)->prev;
			(*lst)->prev->next = new;
			(*lst)->prev = new;
		}
		else
			*lst = new;
	}
}

void	ft_2lstadd_front(t_2list **a, t_2list *new)
{
	if (a)
	{
		if (*a)
			ft_2lstadd_back(a, new);
		*a = new;
	}
}

// Delete node element and points **lst to the next one
void	ft_2lstdelone(t_2list **lst)
{
	t_2list	*deb;

	deb = 0;
	if (lst && *lst)
	{
		if ((*lst)->next != *lst)
		{
			deb = (*lst)->next;
			(*lst)->prev->next = (*lst)->next;
			(*lst)->next->prev = (*lst)->prev;
		}
		free(*lst);
		*lst = 0;
		if (deb)
			*lst = deb;
	}
}

void	*ft_2lstclear(t_2list **a)
{
	t_2list	*tmp;
	t_2list	*deb;

	deb = *a;
	if (a)
	{
		while (*a)
		{
			tmp = *a;
			*a = (*a)->next;
			free(tmp);
			if (*a == deb)
				break ;
		}
		*a = 0;
	}
	return (0);
}
