/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_statics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:24:19 by rficht            #+#    #+#             */
/*   Updated: 2023/05/31 11:05:36 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * enum that represent how the signals will be interpreteed depending on where
 * they are catched
 * @param val Will remplace interactive if >= 0.
 * return Value of interactive.
 */
int	stat_sig(int val)
{
	static t_sig	state;

	if (val >= 0)
		state = val;
	return (state);
}

/**
 * Allow to simulate a global var.
 * @param val Will remplace err if >= 0.
 * return Value of err.
 */
int	stat_err(int val)
{
	static int	err;

	if (val >= 0)
		err = val;
	return (err);
}
