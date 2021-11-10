/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:56:31 by zminhas           #+#    #+#             */
/*   Updated: 2021/11/10 17:40:20 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	char	*str;
	int	fd;

	fd = open("text.txt", O_RDONLY);
	while ((str = get_next_line(fd)))
	{
		//printf("%s", str);
		free(str);
	}
	close(fd);
	return (0);
}

// la commende : clear && c *.c && ./a.out | cat -e