#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	char	*str;
	int	fd;

	//fd = open("text.txt", O_RDONLY);
	fd = 0;
	while ((str = get_next_line(fd)))
	{
		printf("%s", str);
		free(str);
	}
	close(fd);
	return (0);
}

// la commende : clear && c *.c && ./a.out | cat -e