/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abytko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 18:29:34 by abytko            #+#    #+#             */
/*   Updated: 2018/09/28 17:14:00 by abytko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

unsigned int	ft_shift(unsigned int a)
{
	int	fresh;

	fresh = 0;
	fresh += a << 24 & 0xff000000;
	fresh += a << 8 & 0xff0000;
	fresh += a >> 8 & 0xff00;
	fresh += a >> 24 & 0xff;
	return (fresh);
}

int				reverse(int i)
{
	int new;

	new = 0;
	new += i << 24 & 0xff000000;
	new += i << 8 & 0xff0000;
	new += i >> 8 & 0xff00;
	new += i >> 24 & 0xff;
	return (new);
}

unsigned int	find_newlen(unsigned int inlen)
{
	unsigned int new_len;

	new_len = inlen * 8 + 1;
	while (new_len % 512 != 448)
		new_len++;
	return (new_len / 8);
}
