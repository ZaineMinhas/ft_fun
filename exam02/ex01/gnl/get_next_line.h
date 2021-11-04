#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/uio.h>
# include <sys/types.h>

char	*get_next_line(int fd);

#endif