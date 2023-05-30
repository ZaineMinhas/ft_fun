#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_client {
	int				fd;
	int				id;
	struct s_client	*next;
}				t_client;

t_client	*clients, *tmp;
int			sockfd, max_fd, g_id;

int	extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = malloc(sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char	*str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

void	fatal(int nb) {
	if (nb >= 1)
		close(sockfd);
	if (nb >= 2)
		free(clients);
	write(2, "Fatal error\n", 12);
	exit(1);
}

void	clear_clients(t_client *clients)
{
	t_client	*tmp;

	while (clients)
	{
		tmp = clients->next;
		close(clients->fd);
		free(clients);
		clients = tmp;
	}
	
}

void	init_fdset(fd_set *set_read, t_client *clients)
{
	FD_ZERO(set_read);
	max_fd = sockfd;
	while (clients)
	{
		FD_SET(clients->fd, set_read);
		if (max_fd < clients->fd)
			max_fd = clients->fd;
		clients = clients->next;
	}
	FD_SET(sockfd, set_read);
}

void	send_all(t_client *clients, char *str, int fd)
{
	size_t	len;

	len = strlen(str);
	while (clients)
	{
		if (clients->fd != fd)
			send(clients->fd, str, len, 0);
		clients = clients->next;
	}
	write(1, str, len);
}

int	add_client(t_client **clients, int fd)
{
	t_client	*new;
	t_client	*tmp;

	if (!(new = malloc(sizeof(t_client))) || !clients) {
		if (clients)
			clear_clients(*clients);
		fatal(1);
	}
	new->fd = fd;
	new->id = g_id++;
	new->next = NULL;
	if (!(*clients))
		(*clients) = new;
	else {
		tmp = (*clients);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new->id);
}

int	remove_client(t_client **clients, int fd)
{
	t_client	*prev;
	t_client	*tmp;
	int			id;

	if (!clients)
		fatal(1);
	id = -1;
	prev = NULL;
	tmp = *clients;
	if (tmp && tmp->fd == fd) {
		*clients = tmp->next;
		id = tmp->id;
		close(tmp->fd);
		free(tmp);
	}
	else {
		while (tmp && tmp->fd != fd) {
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp) {
			prev->next = tmp->next;
			id = tmp->id;
			close(tmp->fd);
			free(tmp);
		}
	}
	return (id);
}

int	main(int ac, char **av) {
	struct sockaddr_in	servaddr, cli;
	struct timeval		timeout;
	unsigned int		len;
	ssize_t				size;
	fd_set				set_read;
	char				*buff, str[4200], *msg;
	int					connfd, port, ret, id;

	if (ac != 2) {
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1)
		fatal(0);
	bzero(&servaddr, sizeof(servaddr));

	port = atoi(av[1]);
	if (port <= 0)
		fatal(1);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(port);

	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		fatal(1);
	if (listen(sockfd, 10) != 0)
		fatal(1);

	if (!(clients = malloc(sizeof(t_client))))
		fatal(1);
	
	if (!(buff = malloc(sizeof(4096))))
		fatal(2);

	len = sizeof(cli);
	clients = NULL;

	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	g_id = 0;
	
	while (1)
	{
		init_fdset(&set_read, clients);
		ret = select(max_fd + 1, &set_read, NULL, NULL, &timeout);
		if (ret > 0) {
			if (FD_ISSET(sockfd, &set_read)) {
				connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
				if (connfd >= 0) {
					id = add_client(&clients, connfd);
					if (max_fd < connfd)
						max_fd = connfd;
					sprintf(str, "server: client %d just arrived\n", id);
					send_all(clients, str, connfd);
				}
			}
			else {
				tmp = clients;
				while (tmp) {
					connfd = tmp->fd;
					id = tmp->id;
					tmp = tmp->next;
					if (FD_ISSET(connfd, &set_read)) {
						size = recv(connfd, buff, 4096, 0);
						if (!size) {
							id = remove_client(&clients, connfd);
							if (id != -1) {
								sprintf(str, "server: client %d just left\n", id);
								send_all(clients, str, connfd);
							}
						}
						else if (size > 0) {
							msg = NULL;
							while (extract_message(&buff, &msg)) {
								sprintf(str, "client %d: %s", id, msg);
								send_all(clients, str, connfd);
							}
						}
					}
				}
			}
		}
	}
}

// clear && c mini_serv.c && ./a.out 3000