/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abytko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 13:06:06 by abytko            #+#    #+#             */
/*   Updated: 2018/09/28 14:09:17 by abytko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

char	*g_flag = "pqrs";

void	ft_start_hash(char *str, char flag, unsigned int len)
{
	if (str)
	{
		if (flag == 'p')
			ft_putstr(str);
		g_md5 ? ft_md5(str, len) : ft_sha256(str, len);
		ft_putchar('\n');
	}
}

int		ft_flag_valid(char *argv, int remainder_argc, char *flags, int i)
{
	char			*str;
	int				flag_p;
	unsigned int	len;
	char			*start_flags;

	flag_p = 0;
	str = NULL;
	start_flags = flags;
	if (argv[i] == 's' && argv[i + 1])
		return (ft_string_s(&argv[i + 1], start_flags));
	if (argv[i] == 'p' && flag_p == 0 && (flag_p = 1))
		len = ft_get_string(0, &str);
	else if (argv[i] == 'p')
		ft_string_s("", "q");
	if (!ft_strchr(flags, argv[i]) && argv[i] != 'p')
	{
		flags = ft_strchr(flags, '\0');
		*flags = argv[i];
		flags++;
	}
	if ((ft_strchr(start_flags, 'q') || ft_strchr(start_flags, 'r'))
		&& remainder_argc == 0 && !argv[i + 1])
		len = ft_get_string(0, &str);
	ft_start_hash(str, argv[i], len);
	return (1);
}

int		ft_flag_hash(char *argv, char *flags, int remainder_argc)
{
	int				i;
	char			*start_flags;

	i = 1;
	start_flags = flags;
	while (argv[i])
	{
		if (ft_strchr(g_flag, argv[i]))
		{
			if (!ft_flag_valid(argv, remainder_argc, flags, i))
				return (0);
		}
		else
		{
			ft_printf("%s%c\n%s\n", "md5: illegal option -- ", argv[i],
					"usage: md5 [-pqr] [-s string] [files ...]");
			return (0);
		}
		i++;
	}
	return (1);
}
