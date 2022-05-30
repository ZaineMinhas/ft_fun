#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	x = -1;
	while (str[++x]);
	return (x);
}

void	ft_error(char *str1, char *str2)
{
	write(2, str1, ft_strlen(str1));
	if(str2)
	{
		write(2, str2, ft_strlen(str2));
		write(2, "\n", 1);
	}
	exit (0);
}

char	**sub_argv(char **argv, int start, int end)
{
	int x = 0;
	char	**av = malloc(sizeof(char *) * (end - start + 1));

	while (start < end)
		av[x++] = argv[start++];
	av[x] = NULL;
	return (av);
}

int	main(int argc, char **argv, char **env)
{
	int	i = 1, pos, end, start, fd[2], fd_in;
	pid_t	pid;
	char	**av;

	while (i < argc)
	{
		pos = end = start = i;
		while (pos < argc && strcmp(argv[pos], ";"))
			pos++;
		fd_in = 0;
		while (start < pos)
		{
			end = start;
			while (end < pos && strcmp(argv[end], "|"))
				end++;
			av = sub_argv(argv, start, end);
			if (pipe(fd) == -1)
				ft_error("error: fatal\n", NULL);
			pid = fork();
			if (pid == -1)
				ft_error("error: fatal\n", NULL);
			else if (!pid)
			{
				if (dup2(fd_in, 0) == -1)
					ft_error("error: fatal\n", NULL);
				if (end < pos && dup2(fd[1], 1) == -1)
					ft_error("error: fatal\n", NULL);
				close(fd_in);
				close(fd[0]);
				close(fd[1]);
				if (!strcmp(av[0], "cd"))
				{
					if (end - start != 2)
						ft_error("error: cd: bad arguments", NULL);
					if (chdir(av[1]))
						ft_error("error: cd: cannot change directory ", av[1]);
				}
				else if (execve(av[0], av, env))
					ft_error("error: cannot execute ", av[0]);
				exit (0);
			}
			else
			{
				waitpid(pid, NULL, 0);
				close(fd[1]);
				if (fd_in)
					close(fd_in);
				fd_in = fd[0];
			}
			start = end + 1;
		}
		close(fd_in);
		i = pos + 1;
	}
	return (0);
}