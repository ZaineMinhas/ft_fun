#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct s_zone
{
	int		W;
	int		H;
	char	c;
}				t_zone;

typedef struct s_rec
{
	char	r;
	float	x;
	float	y;
	float	widht;
	float	height;
	char	ink;
}				t_rec;

void	print_draw(char **str, t_zone var)
{
	int	i;
	int	j;

	i = 0;
	while (++i < var.W)
	{
		j = 0;
		while (++j < var.H)
			write(1, &str[j][i], 1);
		write(1, "\n", 1);
	}
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

int	str_err(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

char	**init_backscreen(FILE *file, t_zone *var)
{
	char	**tmp;
	int		i;
	int		j;

	if (fscanf(file, "%d %d %c\n", &var->W, &var->H, &var->c) != 3)
		return (NULL);
	if (var->W <= 0 || var->W > 300 || var->H <= 0 || var->H > 300)
		return (NULL);
	if (!(tmp = (char **)malloc(sizeof(char *) * var->W)))
		return (NULL);
	i = -1;
	while (++i < var->H)
	{
		if (!(tmp[i] = (char *)malloc(sizeof(char) * var->H)))
		{
			while (i--)
				free(tmp[i]);
			tmp = NULL;
			free(tmp);
			return (NULL);
		}
	}
	i = -1;
	while (++i < var->W)
	{
		j = -1;
		while (++j < var->H)
			tmp[i][j] = var->c;
	}
	return (tmp);
}

int		in_rec(int x, int y, t_rec rec)
{
	if (x < rec.x || y < rec.y || x > rec.x + rec.widht || y > rec.y + rec.height)
		return (0);
	if (x - rec.x < 1 || rec.widht + rec.x - x < 1 || y - rec.y < 1 || rec.height + rec.y - y < 1)
		return (2);
	return (1);
}

void	calc_rec(char **draw, t_rec rec, t_zone var)
{
	int	is_in;
	int	x;
	int	y;

	x = -1;
	while (++x < var.W)
	{
		y = -1;
		while (++y < var.H)
		{
			is_in = in_rec(x, y, rec);
			if ((rec.r == 'r' && is_in == 2) || (rec.r == 'R' && is_in))
				draw[x][y] = rec.ink;
		}
	}
}

int	draw_rec(char **draw, FILE *file, t_zone var)
{
	t_rec	rec;
	int		ret;

	while ((ret = fscanf(file, "%c %f %f %f %f %c\n", &rec.r, &rec.x, &rec.y, &rec.widht, &rec.height, &rec.ink)) == 6)
	{
		if (rec.widht <= 0 || rec.height <= 0 || (rec.r != 'r' && rec.r != 'R'))
			return (0);
		calc_rec(draw, rec, var);
	}
	if (ret != -1)
		return (0);
	return (1);
}

int	clear_all(FILE *file, t_zone var, char **draw, char *str)
{
	int	i;

	if (file)
		fclose(file);
	if (draw)	
	{
		i = -1;
		while (++i < var.W)
			free(draw[i]);
		free(draw);
	}
	if (str)
		str_err(str);
	return (1);
}

int main(int ac, char **av)
{
	FILE	*file;
	t_zone	var;
	char	**draw;

	if (ac != 2)
		return (str_err("Error: argument\n"));
	if (!(file = fopen(av[1], "r")))
		return (str_err("Error: Operation file corrupted\n"));
	var.c = 0;
	var.H = 0;
	var.W = 0;
	draw = NULL;
	if (!(draw = init_backscreen(file, &var)))
		return (str_err("Error: Operation file corrupted\n"));
	if (!draw_rec(draw, file, var))
		return (clear_all(file, var, draw, "Error: Operation file corrupted\n"));
	print_draw(draw, var);
	clear_all(file, var, draw, NULL);
	return (0);
}
