/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abytko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:59:01 by abytko            #+#    #+#             */
/*   Updated: 2018/09/28 17:02:16 by abytko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H
# include "../lib/libft/libft.h"
# include "ft_printf.h"
# include "../lib/libft/get_next_line.h"
# include <errno.h>
# include <math.h>
# include <fcntl.h>

# define BUF_SIZE 5000

int					g_md5;

typedef struct		s_md5_const
{
	unsigned int	a_cons;
	unsigned int	b_cons;
	unsigned int	c_cons;
	unsigned int	d_cons;
	unsigned int	aa;
	unsigned int	bb;
	unsigned int	cc;
	unsigned int	dd;
	unsigned int	buf[16];
	unsigned int	f;
	unsigned int	g;
	uint64_t		bits;
}					t_md5_const;

typedef struct		s_sha256
{
	unsigned int	a_cons;
	unsigned int	b_cons;
	unsigned int	c_cons;
	unsigned int	d_cons;
	unsigned int	e_cons;
	unsigned int	f_cons;
	unsigned int	g_cons;
	unsigned int	h_cons;
	unsigned int	aa;
	unsigned int	bb;
	unsigned int	cc;
	unsigned int	dd;
	unsigned int	ee;
	unsigned int	ff;
	unsigned int	gg;
	unsigned int	hh;
	unsigned int	new_length;
	unsigned int	s0;
	unsigned int	s1;
	unsigned int	ch;
	unsigned int	t1;
	unsigned int	t2;
	unsigned int	ma;
	uint64_t		bits;
}					t_sha256;

void				ft_md5(char *str, unsigned int length);
unsigned int		ft_shift(unsigned int a);
void				ft_file(char *argv, char *flags);
int					ft_flag_hash(char *argv, char *flags, int remainder_argc);
int					ft_string_s(char *str, char *flags);
unsigned int		ft_get_string(int fd, char **str);
unsigned int		find_newlen(unsigned int inlen);
void				ft_sha256(char *str, unsigned int length);
void				sha256(unsigned char *input);

#endif
