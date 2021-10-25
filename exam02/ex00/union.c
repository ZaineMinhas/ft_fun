/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 12:51:05 by zminhas           #+#    #+#             */
/*   Updated: 2021/10/25 17:57:52 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int ac, char **av)
{
	int	i;
	int	j;
	int	bool;

	if (ac != 3)
		return (write(1, "\n", 1));
	i = -1;
	while (av[1][++i])
	{
		bool = 0;
		j = -1;
		while (++j < i)
			if (av[1][i] == av[1][j])
				bool = 1;
		if (!bool)
			write(1, &av[1][i], 1);
	}
	i = -1;
	while (av[2][++i])
	{
		bool = 0;
		j = -1;
		while (av[1][++j])
			if (av[2][i] == av[1][j])
				bool = 1;
		j = -1;
		while (++j < i)
			if (av[2][i] == av[2][j])
				bool = 1;
		if (!bool)
			write(1, &av[2][i], 1);
	}
	return (write(1, "\n", 1));
}
