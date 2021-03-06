/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlench.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abytko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 21:12:43 by abytko            #+#    #+#             */
/*   Updated: 2018/01/18 17:31:57 by abytko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlench(const char *str, char c)
{
	size_t i;

	i = 0;
	while (*(str + i))
	{
		if ((*(str + i)) == c)
			return (i);
		i++;
	}
	return (0);
}
