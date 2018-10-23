/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_view_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abytko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:49:50 by abytko            #+#    #+#             */
/*   Updated: 2018/09/28 17:14:06 by abytko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

unsigned int	ft_get_string(int fd, char **str)
{
	int		sum;
	int		ret;
	char	buff[BUF_SIZE];
	char	*temp;
	char	*line;

	line = (char *)malloc(BUF_SIZE);
	sum = 0;
	while ((ret = read(fd, buff, BUF_SIZE)))
	{
		ft_memcpy(&line[sum], buff, ret);
		sum = sum + ret;
		temp = line;
		line = (char *)malloc(sum + BUF_SIZE + 1);
		ft_memcpy(line, temp, sum);
		free(temp);
	}
	line[sum] = '\0';
	*str = line;
	return (sum);
}

int				ft_string_s(char *str, char *flags)
{
	unsigned int	len;
	char			*string;

	if (ft_strchr(flags, 'r') && !ft_strchr(flags, 'q'))
	{
		g_md5 ? ft_md5(str, ft_strlen(str)) : ft_sha256(str, ft_strlen(str));
		ft_printf(" \"%s\"", str);
	}
	else if (ft_strchr(flags, 'q'))
		g_md5 ? ft_md5(str, ft_strlen(str)) : ft_sha256(str, ft_strlen(str));
	else if (ft_strchr(flags, 'p'))
	{
		len = ft_get_string(0, &string);
		ft_putstr(string);
		g_md5 ? ft_md5(string, len) : ft_sha256(string, len);
	}
	else
	{
		g_md5 ? ft_printf("%s%s%s", "MD5 (\"", str, "\") = ") :
			ft_printf("%s%s%s", "SHA256 (\"", str, "\") = ");
		g_md5 ? ft_md5(str, ft_strlen(str)) : ft_sha256(str, ft_strlen(str));
	}
	ft_putchar('\n');
	return (0);
}

void			ft_error(char *flags, char *argv)
{
	if (flags)
		flags = NULL;
	if (g_md5)
		ft_printf("%s%s%s%s", "ft_ssl: md5: ", argv, ": ", strerror(errno));
	else
		ft_printf("%s%s%s%s", "ft_ssl: sha256: ", argv, ": ",
				strerror(errno));
}

void			ft_file(char *argv, char *flags)
{
	char			*str;
	int				fd;
	int				i;
	unsigned int	len;

	i = 0;
	if ((fd = open(argv, O_RDONLY)) == -1)
	{
		ft_error(flags, argv);
		return ;
	}
	len = ft_get_string(fd, &str);
	if (!ft_strchr(flags, 'q') && !ft_strchr(flags, 'r'))
	{
		g_md5 ? ft_printf("%s%s%s", "MD5 (", argv, ") = ") :
						ft_printf("%s%s%s", "SHA256 (", argv, ") = ");
	}
	if (g_md5)
		ft_md5(str, len);
	else
		ft_sha256(str, len);
	if (ft_strchr(flags, 'r') && !ft_strchr(flags, 'q'))
		ft_printf(" %s", argv);
	free(str);
}
