#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

typedef	struct 	s_zone
{
	int			width;
	int			height;
	char		background;
}				t_zone;

typedef	struct 	s_shape
{
	float		x;
	float		y;
	float		radius;
	char		type;
	char		color;
}				t_shape;


char *get_zone(FILE *file, t_zone *zone)
{
	char	*draw_buff;
	int		i;

	i = 0;
	if (fscanf(file, "%d %d %c\n", &zone->width, &zone->height, &zone->background) != 3)
		return NULL;
	if (zone->width <= 0.0 || zone->width > 300 || zone->height <= 0. || zone->height > 300)
		return NULL;
	if (!(draw_buff = (char *)malloc(sizeof (char) * (zone->width * zone->height))))
		return NULL;
	while (i < zone->width * zone->height)
	{
		draw_buff[i] = zone->background;
		i++;
	}
	return draw_buff;

}

int	draw_shapes(char *draw_buff, t_zone *zone, FILE *file)
{
	t_shape shape;
	int ret;
	int x;
	int y;
	float distance;

	while((ret = fscanf(file, "%c %f %f %f %c\n", &shape.type, &shape.x, &shape.y, &shape.radius, &shape.color)) == 5)
	{
		if (shape.radius <= 0 || (shape.type != 'c' && shape.type != 'C'))
			return 0;
		y = 0;
		while (y < zone->height)
		{
			x = 0;
			while (x < zone->width)
			{
				distance = sqrt(powf(x - shape.x, 2.) + powf(y - shape.y, 2.));
				if (distance <= shape.radius)
				{
					if ((shape.type == 'c' && (shape.radius - distance < 1.0))
						|| (shape.type == 'C'))
					{
						draw_buff[(y * zone->width) + x] = shape.color;
					}
				}
				x++;
			}
			y++;
		}
		
	}
	if (ret != -1)
		return 0;
	return 1;
}

int	main(int argc, char **argv)
{
	t_zone	zone;
	FILE	*file;
	char	*draw_buff;

	zone.background = 0;
	zone.height = 0;
	zone.width = 0;
	draw_buff = NULL;

	if (argc != 2)
	{
		printf("Error: argument\n");
		return (1);
	}
	if (!(file = fopen(argv[1], "r")))
	{
		printf("Error: Operation file corrupted\n");
		return (1);
	}
	draw_buff = get_zone(file, &zone);
	if (!(draw_shapes(draw_buff, &zone, file)))
	{
		printf("Error: Operation file corrupted\n");
		return (1);
	}
	
	int	i;

	i = 0;
	while (i < zone.height)
	{
		write(1, draw_buff + (i * zone.width), zone.width);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}