/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:02:13 by zminhas           #+#    #+#             */
/*   Updated: 2021/11/03 17:05:59 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

char    *free_ret(void *mem, void *ret);
int    ft_index(char *str, char c);
int    ft_strlen(char *str);
char    *ft_strjoin(char *str1, char *str2);
char *ft_substr(char *str, int start, int end, int free_str);
char    *get_next_line(int fd);

#endif
