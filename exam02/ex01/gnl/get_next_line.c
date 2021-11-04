#include "get_next_line.h"

char	*ft_check(int fd)
{
	char	*buff;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	return (buff);
}

int	ft_strlen(char *str)
{
	int	i;
	
	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_index(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	if (str[i] == c)
		return (i);
	return (-1);
}

char	*ft_gnljoin(char *str1, char *str2)
{
	char	*dest;
	int		size;
	int		i;

	size = ft_strlen(str1) + ft_strlen(str2);
	dest = malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	i = -1;
	if (str1)
		while (str1[++i])
			dest[i] = str1[i];
	size = -1;
	if (str2)
	{
		if (i == -1)
			i = 0;
		while (str2[++size])
			dest[i + size] = str2[size];
	}
	dest[i + size] = 0;
	free(str1);
	return (dest);
}

char	*ft_substr(char *str, int start, int end, int to_free)
{
	char	*dest;
	int		i;

	if (end < 1)
	{
		//printf("salut\n");
		end = ft_strlen(str);
	}

	if (!str || start < 0 || start >= end || end > ft_strlen(str))
	{
		if (to_free)
			free(str);
		return (NULL);
	}
	dest = malloc(sizeof(char) * (end - start + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (str[start + ++i] && (start + i) < end)
		dest[i] = str[start + i];
	dest[i] = 0;
	if (to_free)
		free(str);
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	char		*buff;
	int			reader;

	buff = ft_check(fd);
	if (!buff)
		return (NULL);
	reader = 1;
	while (ft_index(save, '\n') < 0 && reader)
	{
		reader = read(fd, buff, BUFFER_SIZE);
		buff[reader] = 0;
		save = ft_gnljoin(save, buff);
		if (!save)
			return (NULL);
	}
	free(buff);
	line = ft_substr(save, 0, ft_index(save, '\n') + 1, 0);
	save = ft_substr(save, ft_index(save, '\n') + 1, ft_strlen(save), 1);
	return (line);
}


// la commende : clear && c *.c && ./a.out | cat -e