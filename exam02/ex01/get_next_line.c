/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:00:51 by zminhas           #+#    #+#             */
/*   Updated: 2021/11/03 17:33:46 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_ret(void *mem, void *ret)
{
	free(mem);
	return (ret);
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
	return (-1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*str;
	char	*ptr;
	int		tot_len;
	int		i;

	tot_len = ft_strlen(str1) + ft_strlen(str2);
	str = (char *)malloc(sizeof(char) * tot_len + 1);
	if (!str)
		return (NULL);
	ptr = str;
	i = -1;
	while (str1 && str1[++i])
		*ptr++ = str1[i];
	i = -1;
	while (str2 && str2[++i])
		*ptr++ = str2[i];
	*ptr = 0;
	if (str1)
		free(str1);
	return (str);
}

char	*ft_substr(char *str, int start, int end, int free_str)
{
	char	*substr;
	int		i;

	if (!str || start >= end || start < 0 || end > ft_strlen(str))
	{
		if (free_str)
			free(str);
		return (NULL);
	}
	substr = (char *)malloc(sizeof(char) * (end - start + 1));
	i = -1;
	while (str[start + ++i] && (start + i) != end)
		substr[i] = str[start + i];
	substr[i] = 0;
	if (free_str)
		free(str);
	return (substr);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;
	char		*buff;
	int			bytes;

	buff = (char *)calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes = 1;
	while (ft_index(saved, '\n') < 0 && bytes)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		buff[bytes] = 0;
		saved = ft_strjoin(saved, buff);
		if (!saved)
			return (free_ret(buff, NULL));
	}
	free(buff);
	line = ft_substr(saved, 0, ft_index(saved, '\n') + 1, 0);
	saved = ft_substr(saved, ft_index(saved, '\n') + 1, ft_strlen(saved), 1);
	return (line);
}
