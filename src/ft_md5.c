/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abytko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 18:34:24 by abytko            #+#    #+#             */
/*   Updated: 2018/09/28 17:14:03 by abytko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

unsigned int	g_a = 0x67452301;
unsigned int	g_b = 0xefcdab89;
unsigned int	g_c = 0x98badcfe;
unsigned int	g_d = 0x10325476;
unsigned int	g_wn[64];
unsigned int	g_r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static void	md5_initialize(t_md5_const *abcd)
{
	double	abs;
	double	power;
	int		i;

	abcd->a_cons = g_a;
	abcd->b_cons = g_b;
	abcd->c_cons = g_c;
	abcd->d_cons = g_d;
	i = 0;
	power = pow(2, 32);
	while (i < 64)
	{
		abs = fabs(sin(i + 1));
		g_wn[i] = abs * power;
		i++;
	}
}

static void	ft_set_buf(t_md5_const *md, unsigned char *all_str, int i)
{
	int	j;

	j = 0;
	while (j < 16)
	{
		md->buf[j] = 0;
		md->buf[j] += all_str[i * 64 + j * 4 + 0];
		md->buf[j] += all_str[i * 64 + j * 4 + 1] << 8;
		md->buf[j] += all_str[i * 64 + j * 4 + 2] << 16;
		md->buf[j] += all_str[i * 64 + j * 4 + 3] << 24;
		j++;
	}
	md->aa = md->a_cons;
	md->bb = md->b_cons;
	md->cc = md->c_cons;
	md->dd = md->d_cons;
}

static void	ft_logic_func(t_md5_const *md, int j)
{
	if (j < 16)
	{
		md->f = (md->bb & md->cc) | ((~md->bb) & md->dd);
		md->g = j;
	}
	else if (j < 32)
	{
		md->f = (md->dd & md->bb) | ((~md->dd) & md->cc);
		md->g = (5 * j + 1) & 15;
	}
	else if (j < 48)
	{
		md->f = md->bb ^ md->cc ^ md->dd;
		md->g = (3 * j + 5) & 15;
	}
	else
	{
		md->f = md->cc ^ (md->bb | (~md->dd));
		md->g = (7 * j) & 15;
	}
	md->f = md->f + md->aa + g_wn[j] + md->buf[md->g];
	md->aa = md->dd;
	md->dd = md->cc;
	md->cc = md->bb;
	md->bb += ((md->f << g_r[j]) | (md->f >> (32 - g_r[j])));
}

static void	ft_main_loop(t_md5_const *abcd, unsigned char *all_str,
										unsigned int new_length)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < (new_length + 8) / 64)
	{
		j = -1;
		ft_set_buf(abcd, all_str, i);
		while (++j < 64)
			ft_logic_func(abcd, j);
		abcd->a_cons += abcd->aa;
		abcd->b_cons += abcd->bb;
		abcd->c_cons += abcd->cc;
		abcd->d_cons += abcd->dd;
		i++;
	}
}

void		ft_md5(char *str, unsigned int length)
{
	unsigned int		new_length;
	unsigned char		*all_str;
	t_md5_const			abcd;

	new_length = find_newlen(length);
	all_str = (unsigned char *)malloc(new_length + 64);
	ft_bzero(all_str, new_length + 64);
	ft_memcpy(all_str, str, length);
	all_str[length] = 0x80;
	abcd.bits = 8 * length;
	memcpy(all_str + new_length, &abcd.bits, 8);
	md5_initialize(&abcd);
	ft_main_loop(&abcd, all_str, new_length);
	abcd.a_cons = ft_shift(abcd.a_cons);
	abcd.b_cons = ft_shift(abcd.b_cons);
	abcd.c_cons = ft_shift(abcd.c_cons);
	abcd.d_cons = ft_shift(abcd.d_cons);
	ft_printf("%.8x%.8x%.8x%.8x", abcd.a_cons, abcd.b_cons, abcd.c_cons,
			abcd.d_cons);
	free(all_str);
}
