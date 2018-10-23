/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abytko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 14:10:49 by abytko            #+#    #+#             */
/*   Updated: 2018/09/27 17:13:21 by abytko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

unsigned int	g_aa = 0x6a09e667;
unsigned int	g_bb = 0xbb67ae85;
unsigned int	g_cc = 0x3c6ef372;
unsigned int	g_dd = 0xa54ff53a;
unsigned int	g_ee = 0x510e527f;
unsigned int	g_ff = 0x9b05688c;
unsigned int	g_gg = 0x1f83d9ab;
unsigned int	g_hh = 0x5be0cd19;
unsigned int	g_buf[64];
unsigned int	g_rr[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

static unsigned int	rotate_rigth(unsigned int n, unsigned int rotr)
{
	unsigned int	i;
	unsigned int	res;

	i = 0;
	while (i < rotr)
	{
		res = n & 1;
		n = n >> 1;
		n += res << 31;
		i++;
	}
	return (n);
}

static void			ft_set_buf(t_sha256 *sha, unsigned char *all_str, int i)
{
	unsigned int	j;

	j = 0;
	while (j < 16)
	{
		g_buf[j] = 0;
		g_buf[j] += all_str[i * 64 + j * 4 + 0] << 24;
		g_buf[j] += all_str[i * 64 + j * 4 + 1] << 16;
		g_buf[j] += all_str[i * 64 + j * 4 + 2] << 8;
		g_buf[j] += all_str[i * 64 + j * 4 + 3];
		j++;
	}
	while (j < 64)
	{
		sha->s0 = rotate_rigth(g_buf[j - 15], 7) ^ rotate_rigth(g_buf[j - 15], \
					18) ^ (g_buf[j - 15] >> 3);
		sha->s1 = rotate_rigth(g_buf[j - 2], 17) ^ rotate_rigth(g_buf[j - 2], \
					19) ^ (g_buf[j - 2] >> 10);
		g_buf[j] = g_buf[j - 16] + sha->s0 + g_buf[j - 7] + sha->s1;
		j++;
	}
	sha->aa = sha->a_cons;
	sha->bb = sha->b_cons;
	sha->cc = sha->c_cons;
	sha->dd = sha->d_cons;
}

static void			ft_logic_func(t_sha256 *sha, unsigned int j)
{
	sha->s0 = rotate_rigth(sha->aa, 2) ^ rotate_rigth(sha->aa, 13) ^ \
					rotate_rigth(sha->aa, 22);
	sha->ma = (sha->aa & sha->bb) ^ (sha->aa & sha->cc) ^ (sha->bb & sha->cc);
	sha->t2 = sha->s0 + sha->ma;
	sha->s1 = rotate_rigth(sha->ee, 6) ^ rotate_rigth(sha->ee, 11) ^ \
						rotate_rigth(sha->ee, 25);
	sha->ch = (sha->ee & sha->ff) ^ ((~sha->ee) & sha->gg);
	sha->t1 = sha->hh + sha->s1 + sha->ch + g_rr[j] + g_buf[j];
	sha->hh = sha->gg;
	sha->gg = sha->ff;
	sha->ff = sha->ee;
	sha->ee = sha->dd + sha->t1;
	sha->dd = sha->cc;
	sha->cc = sha->bb;
	sha->bb = sha->aa;
	sha->aa = sha->t1 + sha->t2;
}

static void			ft_main_loop(t_sha256 *sha, unsigned char *all_str)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < (sha->new_length + 8) / 64)
	{
		j = -1;
		ft_set_buf(sha, all_str, i);
		sha->ee = sha->e_cons;
		sha->ff = sha->f_cons;
		sha->gg = sha->g_cons;
		sha->hh = sha->h_cons;
		while (++j < 64)
			ft_logic_func(sha, j);
		sha->a_cons = sha->a_cons + sha->aa;
		sha->b_cons = sha->b_cons + sha->bb;
		sha->c_cons = sha->c_cons + sha->cc;
		sha->d_cons = sha->d_cons + sha->dd;
		sha->e_cons = sha->e_cons + sha->ee;
		sha->f_cons = sha->f_cons + sha->ff;
		sha->g_cons = sha->g_cons + sha->gg;
		sha->h_cons = sha->h_cons + sha->hh;
		i++;
	}
}

void				ft_sha256(char *str, unsigned int length)
{
	unsigned int	i;
	unsigned char	*all_str;
	t_sha256		sha;

	sha.new_length = find_newlen(length);
	all_str = (unsigned char *)malloc(sha.new_length + 64);
	ft_bzero(all_str, sha.new_length + 64);
	ft_memcpy(all_str, str, length);
	all_str[length] = 0x80;
	sha.bits = 8 * length;
	i = -1;
	while (++i < 8)
		all_str[sha.new_length + i] = ((unsigned char *)&(sha.bits))[7 - i];
	sha.a_cons = g_aa;
	sha.b_cons = g_bb;
	sha.c_cons = g_cc;
	sha.d_cons = g_dd;
	sha.e_cons = g_ee;
	sha.f_cons = g_ff;
	sha.g_cons = g_gg;
	sha.h_cons = g_hh;
	ft_main_loop(&sha, all_str);
	ft_printf("%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x", sha.a_cons, sha.b_cons, \
		sha.c_cons, sha.d_cons, sha.e_cons, sha.f_cons, sha.g_cons, sha.h_cons);
	free(all_str);
}
