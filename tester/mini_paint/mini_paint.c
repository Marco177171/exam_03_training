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

void ft_free_matrix(char **matrix)
{
	int index;

	index = -1;
	while (matrix[++index])
		free(matrix[index]);
	free(matrix);
}

int main(int argc, char *argv[])
{
	FILE *file;
	int height, width, x_index, y_index, check;
	char fill, background, id;
	float x_center, y_center, radius;
	char **result;

	if (argc != 2)
		return (ft_error("Error: argument\n"));
	file = fopen(argv[1], "r");
	if (!file)
		return (ft_error("Error: Operation file corrupted\n"));
	if (fscanf(file, "%c %d %d\n", &background, &width, &height) != 3)
		return (ft_error("Error: Operation file corrupted\n"));
	if (width < 1 || width > 300 || height < 1 || height > 300)
		return (ft_error("Error: Operation file corrupted\n"));
	result = malloc(sizeof(char*) * height + 1);
	y_index = -1;
	while (++y_index < height + 1)
	{
		result[y_index] = malloc(sizeof(char) * width + 1);
		memset(result[y_index], background, width + 1);
		result[y_index][width + 1] = '\0';
	}
	result[height + 1] = NULL;
	if (!result)
		return (ft_error("Error: Operation file corrupted\n"));
	while (fscanf(file, "%c %f %f %f %c\n", &id, &x_center, &y_center, &radius, &fill) == 5)
	{
		if (radius < 0.000000000 || (id != 'c' && id != 'C'))
			return (ft_error("Error: Operation file corrupted"));
		y_index = -1;
		while (++y_index < height + 1)
		{
			x_index = -1;
			while (++x_index < width + 1)
			{
				check = ft_check(x_center, y_center, (float)x_index, (float)y_index, radius);
				if (check == 2 || (check == 1 && id == 'C'))
					result[y_index][x_index] = fill;
			}
		}
	}
	y_index = -1;
	while (++y_index < height + 1)
	{
		write(1, result[y_index], ft_strlen(result[y_index]));
		write(1, "\n", 1);
	}
	ft_free_matrix(result);
	fclose(file);
	return (0);
}

