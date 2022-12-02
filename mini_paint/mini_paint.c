#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

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

int ft_check(float x_center, float y_center, float x_index, float y_index, float radius)
{
	float distance;

	distance = sqrtf(powf(x_center - x_index, 2.) + powf(y_center - y_index, 2.));
	if ((int)distance < (int)radius)
		return (1); // inner pixel
	else if ((int)distance == (int)radius)
		return (2); // outline;
	return (0); // background
}

int main(int argc, char *argv[])
{
	FILE *file;
	int height, width, x_index, y_index, check;
	char fill, background, id;
	float x_center, y_center, radius;
	char *result;

	if (argc != 2)
		return (ft_error("Error: argument\n"));
	file = fopen(argv[1], "r");
	if (!file)
		return (ft_error("Error: Operation file corrupted\n"));
	if (fscanf(file, "%c %d %d\n", &background, &width, &height) != 3)
		return (ft_error("Error: Operation file corrupted\n"));
	if (width < 1 || width > 300 || height < 1 || height > 300)
		return (ft_error("Error: Operation file corrupted\n"));
	result = malloc(sizeof(char) * width * height + height);
	if (!result)
		return (ft_error("Error: Operation file corrupted\n"));
	result[width * height + height] = '\0';
	while (fscanf(file, "%c %f %f %f %c\n", &id, &x_center, &y_center, &radius, &fill) == 5)
	{
		if (radius < 0.000000000)
			return (ft_error("Error: operation file corrupted"));
		y_index = -1;
		while (++y_index < height)
		{
			x_index = -1;
			while (++x_index < width)
			{
				check = ft_check(x_center, y_center, (float)x_index, (float)y_index, radius);
				if (x_index == width - 1)
					result[y_index * x_index] = '\n';
				else if (check == 2 || (check == 1 && id == 'C'))
					result[y_index * x_index] = fill;
				else
					result[y_index * x_index] = background;
			}
		}
	}
	write(1, result, ft_strlen(result));
	free(result);
	fclose(file);
	return (0);
}

