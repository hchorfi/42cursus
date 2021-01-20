#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

typedef struct 	s_zone
{
	int width;
	int height;
	char background;
}				t_zone;

typedef struct 	s_shape
{
	char type;
	float width;
	float height;
	float radius;
	char color;
}				t_shape;


int str_error(char *str)
{
	write(1, str, ft_stren);
}

int main(int argc, char **argv)
{
	FILE *file;
	t_zone zone;
	char *drawing;

	if (argc != 2)
		str_error("Error: argument\n");

}