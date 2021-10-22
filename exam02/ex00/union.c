/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 12:51:05 by zminhas           #+#    #+#             */
/*   Updated: 2021/10/22 13:02:07 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int ac, char **av)
{
	char	str[256];
	int	bool;
	int	i;
	int	j;

	if (ac != 3)
		return (write(1, "\n", 1));
	i = -1;
	while (av[1][++i])
	{
		bool = 0;
		j = -1;
		while (str[++j])
			if (av[1][i] == str[j])
				bool = 1;
		if (!bool)
		{
			str[j] = av[1][i];
			write(1, &av[1][i], 1);
		}
	}
	i = -1;
	while (av[2][++i])
	{
		bool = 0;
		j = -1;
		while (str[++j])
			if (av[2][i] == str[j])
				bool = 1;
		if (!bool)
		{
			str[j] = av[2][i];
			write(1, &av[2][i], 1);
		}
	}
	return (write(1, "\n", 1));
}