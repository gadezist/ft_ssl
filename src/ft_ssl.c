/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abytko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 12:22:14 by abytko            #+#    #+#             */
/*   Updated: 2018/09/28 17:03:13 by abytko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	ft_display_hash(char *flags, int argc)
{
	unsigned int	len;
	char			*str;

	if (ft_strchr(flags, 's') && g_md5)
		ft_printf("%s\n%s\n", "ft_ssl: md5: option requires an argument \
					-- s", "usage:md5 [-pqr] [-s string] [files ...]");
	else if (ft_strchr(flags, 's') && !g_md5)
		ft_printf("%s\n%s\n", "ft_ssl: sha256: option requires anargument \
					-- s", "usage:md5 [-pqr] [-s string] [files ...]");
	else if (argc == 2)
	{
		len = ft_get_string(0, &str);
		if (g_md5)
			ft_md5(str, len);
		else
			ft_sha256(str, len);
		ft_putchar('\n');
	}
}

void	ft_find_flags(char **argv, char *flags, int argc)
{
	int	i;

	i = 2;
	while (i < argc)
	{
		if (ft_strchr(flags, 's'))
		{
			ft_string_s(argv[i], flags);
			ft_bzero(ft_strchr(flags, 's'), 1);
		}
		else if (argv[i][0] == '-' && argv[i][1])
			ft_flag_hash(argv[i], flags, (argc - i - 1));
		else
		{
			while (i != argc)
			{
				ft_file(argv[i], flags);
				ft_putchar('\n');
				i++;
			}
		}
		i++;
	}
}

int		ft_valid(char **argv, int argc)
{
	int				i;
	char			flags[5];

	g_md5 = 0;
	i = -1;
	ft_bzero(flags, 5);
	while (argv[1][++i])
		argv[1][i] = ft_tolower(argv[1][i]);
	if ((g_md5 = ft_strequ(argv[1], "md5")) || ft_strequ(argv[1], "sha256"))
	{
		ft_find_flags(argv, flags, argc);
		ft_display_hash(flags, argc);
		return (1);
	}
	ft_printf("%s%s%s\n\n%s\n\n%s\n%s\n%s\n%s\n", "ft_ssl: Error: '", argv[1],
			"' is an invalid command.", "Standard commands:",
			"Message Digest commands:", "md5", "sha256", "Cipher commands:");
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc > 1)
	{
		if (!ft_valid(argv, argc))
			return (0);
	}
	else
		ft_printf("%s\n", "usage: ft_ssl command [command opts]"
					"[command args]");
	return (0);
}
