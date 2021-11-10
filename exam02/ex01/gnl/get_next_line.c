#include "get_next_line.h"

char	*ft_check(int fd)
{
	char	*buff;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE < 1)
		return (NULL);
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	return (buff);
}

int		ft_index(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

int		ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*gnljoin(char *str1, char *str2)
{
	char	*dest;
	int		size;
	int		i;

	 size = ft_strlen(str1) + ft_strlen(str2) + 1;
	 dest = malloc(sizeof(char) * size);
	 if (!dest)
	 	return (NULL);
	i = -1;
	if (str1)
		while (str1[++i])
			dest[i] = str1[i];
	size = -1;
	if (i == -1)
		i = 0;
	while (str2[++size])
		dest[i + size] = str2[size];
	dest[i + size] = 0;
	if (str1)
		free(str1);
	return (dest);
}

char	*get_line(char *str)
{
	char	*line;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	j = -1;
	while (++j < i)
		line[j] = str[j];
	line[j] = 0;
	return (line);
}

char	*ft_strdup(char *str)
{
	char	*dest;
	int		i;

	if (!str)
		return (NULL);
	dest = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dest)
		return (NULL);
	i = -1;
	while (str[++i])
		dest[i] = str[i];
	dest[i] = 0;
	return (dest);
}

char	*get_after_line(char *save)
{
	char	*dest;
	int		i;

	i = -1;
	while (save[++i])
	{
		if (save[i] == '\n')
		{
			dest = ft_strdup(save + i + 1);
			free(save);
			return (dest);
		}
	}
	free(save);
	return (NULL);
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
		if (reader < 0)
		{
			if (save)
				free(save);
			free(buff);
			return (NULL);
		}
		buff[reader] = 0;
		save = gnljoin(save, buff);
	}
	free(buff);
	printf("|%s|", save);
	if (!reader)
	{
		if (save)
			free(save);
		return (NULL);
	}
	line = get_line(save);
	save = get_after_line(save);
	return (line);
}

