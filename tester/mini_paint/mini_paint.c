#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define ERR1 "Error: argument\n"
#define ERR2 "Error: Operation file corrupted\n"

int ft_strlen(char *str)
{
	int index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

int ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int ft_check(float x, float y, float radius, float x_index, float y_index)
{
	float distance;

	distance = sqrtf(powf(x_index - x, 2.) + powf(y_index - y, 2.));
	if (distance - radius <= 0.00000000 && distance - radius > -1.00000000)
		return (1); // outline
	if (distance - radius <= -1.00000000)
		return (2);
	return (0);
}

int main(int argc, char *argv[])
{
	FILE *file;
	int width, height, y_index, x_index;
	float radius, x, y;
	char background, fill, id;
	char **result;

	if (argc != 2)
		return (ft_error(ERR1));
	file = fopen(argv[1], "r");
	if (!file)
		return (ft_error(ERR2));
	if (fscanf(file, "%d %d %c\n", &width, &height, &background) != 3)
		return (ft_error(ERR2));
	if (width < 1 || width > 300 || height < 1 || height > 300)
		return (ft_error(ERR2));
	result = malloc(sizeof(char *) * height);
	result[height] = NULL;
	if (!result)
		return (ft_error(ERR2));
	y_index = -1;
	while (++y_index < height)
	{
		result[y_index] = malloc(sizeof(char) * width);
		memset(result[y_index], background, width);
		result[y_index][width] = '\0';
	}
	while (fscanf(file, "%c %f %f %f %c\n", &id, &x, &y, &radius, &fill) == 5)
	{
		if (radius <= 0.00000000 || (id != 'c' && id != 'C'))
			return (ft_error(ERR2));
		y_index = -1;
		while (++y_index < height)
		{
			x_index = -1;
			while (++x_index < width)
			{
				if (ft_check(x, y, radius, (float)x_index, (float)y_index) == 1
						|| (ft_check(x, y, radius, (float)x_index, (float)y_index) == 2
						&& id == 'C'))
					result[y_index][x_index] = fill;
			}
		}
	}
	y_index = -1;
	while (++y_index < height)
	{
		write(1, result[y_index], ft_strlen(result[y_index]));
		write(1, "\n", 1);
	}
	fclose(file);
	return (0);
}

