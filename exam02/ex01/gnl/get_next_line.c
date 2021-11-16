#include "get_next_line.h"

char	*ft_check(int fd)
{
	char	*buff;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE < 1)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	return (buff);
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

int		backslash(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (1);
	return (0);
}

char	*gnl_join(char *str1, char *str2)
{
	char	*dest;
	int		size;
	int		i;

	size = ft_strlen(str1) + ft_strlen(str2) + 1;
	dest = malloc(sizeof(char) * size);
	if (!dest)
	{
		if (str1)
			free(str1);
		return (NULL);
	}
	i = -1;
	if (str1)
		while (str1[++i])
			dest[i] = str1[i];
	if (i == -1)
		i = 0;
	size = -1;
	while (str2[++size])
		dest[i +size] = str2[size];
	dest[i +size] = 0;
	if (str1)
		free(str1);
	return (dest);
}

char	*ft_strdup(char *str)
{
	char	*dest;
	int		i;

	if (!str)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dest)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (str[++i])
		dest[i] = str[i];
	dest[i] = 0;
	return (dest);
}

char	*final_line(char *str)
{
	char	*line;

	if (!str[0])
	{
		free(str);
		return (NULL);
	}
	line = ft_strdup(str);
	if (str)
	 	free(str);
	return (line);
}

char	*get_line(char *save, int reader)
{
	char	*line;
	int		i;
	int		j;

	if (!save)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (i == ft_strlen(save) && !reader)
		return (final_line(save));
	i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
	{
		free(save);
		return (NULL);
	}
	j = -1;
	while (++j < i)
		line[j] = save[j];
	line[j] = 0;
	return (line);
}

char	*get_after_line(char *str)
{
	char	*dest;
	int		i;

	if (!str)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\n')
		{
			dest = ft_strdup(str + i + 1);
			free(str);
			return (dest);
		}
	}
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
	while (!backslash(save) && reader)
	{
		reader = read(fd, buff, BUFFER_SIZE);
		if (reader == -1)
		{
			if (save)
				free(save);
			free(buff);
			return (NULL);
		}
		if (!reader)
			break;
		buff[reader] = 0;
		save = gnl_join(save, buff);
		if (!save)
		{
			free(buff);
			return (NULL);
		}
	}
	free(buff);
	if (!save && reader)
		return (NULL);
	line = get_line(save, reader);
	save = get_after_line(save);
	return (line);
}
