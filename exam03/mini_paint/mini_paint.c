#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_zone
{
    char	c;
    int		W;
    int		H;
}               t_zone;

typedef struct s_circle
{
	char	c;
	float	x;
	float	y;
	float	radius;
	char	b_c;
}				t_circle;

void	print_draw(char **tab, t_zone *zone)
{
	int	i;
	int	j;

	i = -1;
	while (++i < zone->H)
	{
		j = -1;
		while (++j < zone->W)
			write(1, &tab[j][i], 1);
		write(1, "\n", 1);
	}
}

int ft_strlen(char *str)
{
    int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int str_err(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

char **init_zone(t_zone *zone, FILE *file)
{
	char	**tab;
	int		i;
	int		j;

	if (fscanf(file, "%d %d %c\n", &zone->W, &zone->H, &zone->c) != 3)
		return (NULL);
	if (zone->W < 0 || zone->W > 300 || zone->H < 0 || zone->H > 300)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (zone->W))))
		return (NULL);
	i = -1;
	while (++i < zone->W)
	{
		if (!(tab[i] = (char *)malloc(sizeof(char) * zone->H)))
		{
			while (i--)
				free(tab[i]);
			free(tab);
			tab = NULL;
			return (NULL);
		}
	}
	i = -1;
	while (++i < zone->W)
	{
		j = -1;
		while (++j < zone->H)
			tab[i][j] = zone->c;
	}
	return (tab);
}

int		in_circle(float x, float y, t_circle *circle)
{
	float	dist;
	dist = sqrtf(powf(x - circle->x, 2) + powf(y - circle->y, 2));
	if (dist <= circle->radius)
	{
		if ((circle->radius - dist) < 1)
			return (2);
		return (1);
	}
	return (0);
}

void	draw_it(char **draw, t_circle *circle, t_zone zone)
{
	int	x;
	int	y;
	int	is_in;

	x = -1;
	while (++x < zone.W)
	{
		y = -1;
		while (++y < zone.H)
		{
			is_in = in_circle((float)x, (float)y, circle);
			if ((circle->c == 'c' && is_in == 2) || (circle->c == 'C' && is_in))
				draw[x][y] = circle->b_c;
		}
	}
}

int	draw_circle(char **draw, FILE *file, t_zone zone)
{
	t_circle 	circle;
	int			ret;

	while ((ret = fscanf(file, "%c %f %f %f %c\n", &circle.c, &circle.x, &circle.y, &circle.radius, &circle.b_c)) == 5)
	{
		if ((circle.c != 'c' && circle.c != 'C') || circle.radius <= 0)
			return (0);
		draw_it(draw, &circle, zone);
	}
	if (ret != -1)
		return (0);
	return (1);
}

int	clear_all(FILE *file, char **draw, t_zone zone, char *str)
{
	int	i;

	if (draw)
	{
		i = -1;
		while (++i < zone.W)
			free(draw[i]);
		free(draw);
	}
	if (file)
		fclose(file);
	if (str)
		str_err(str);
	return (1);
}

int main(int ac, char **av)
{
	t_zone 	zone;
	FILE 	*file;
	char	**to_draw;

	if (ac != 2)
		return (str_err("Error: argument\n"));
	if (!(file = fopen(av[1], "r")))
		return (str_err("Error: Operation file corrupted\n"));
	zone.c = 0;
	zone.H = 0;
	zone.W = 0;
	to_draw = NULL;
	if (!(to_draw = init_zone(&zone, file)))
		return (clear_all(file, to_draw, zone, "Error: Operation file corrupted\n"));
	printf("%d %d %c\n", zone.W, zone.H, zone.c);
	if (!draw_circle(to_draw, file, zone))
		return (clear_all(file, to_draw, zone, "Error: Operation file corrupted\n"));
	print_draw(to_draw, &zone);
	clear_all(file, to_draw, zone, NULL);
	return (0);
}

// clear && gcc mini_pant.c && ./a.out file