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

char *get_zone(FILE *file, t_zone *zone)
{
	char	*draw_buff;
	int		i;

	i = 0;
	if (fscanf(file, "%d %d %c\n", &zone->width, &zone->height, &zone->background) != 3)
		return NULL;
	if (zone->width <= 0 || zone->width > 300 || zone->height <= 0 || zone->height > 300)
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
	int i = 0;
	while (i < zone.width)
	{
		j = 0;
		while (j < zone.height)
		{
			printf("%c", draw_buff[j]);
			j++;
		}
		printf("\n");
		i++;
	}
	return (0);
}