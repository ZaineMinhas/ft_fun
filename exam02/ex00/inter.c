/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 12:43:08 by zminhas           #+#    #+#             */
/*   Updated: 2021/10/23 16:30:29 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	was_in(char *str, int i)
{
	int j;
	
	j = -1;
	while (str[++j] && j < i)
		if (str[j] == str[i])
			return (1);
	return (0);
}

int	main(int ac, char **av)
{
	int	bool;
	int	i;
	int	j;

	if (ac != 3)
		return(write(1, "\n", 1));
	i = -1;
	while (av[1][++i])
	{
		bool = 0;
		j = -1;
		while (av[2][++j])
		{
			if (av[1][i] == av[2][j] && !was_in(av[1], i))
				bool = 1;
		}
		if (bool)
			write(1, &av[1][i], 1);
	}
	return (write(1, "\n", 1));
}
