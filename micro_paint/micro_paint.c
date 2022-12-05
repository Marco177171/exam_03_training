// micro_paint

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define ERR0 "Error: argument\n"
#define ERR1 "Error: Operation file corrupted\n"

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

void ft_free_matrix(char **matrix)
{
	int index;

	index = -1;
	while (matrix[++index])
		free(matrix[index]);
	free(matrix);
}

int ft_check(int x, int y, int r_height, int r_base, int y_index, int x_index)
{
	printf("checking\n");
	if (x_index > x && x_index < x + r_base && y_index > y && y_index < y + r_height)
		return (1); // inner pixel
	else if ((x_index == x || x_index == x + r_base) && (y_index > y && y_index < y + r_height))
		return (2); // vertical border
	else if ((x_index > x && x_index < x + r_base) && (y_index == y || y_index == y + r_height))
		return (3); // horizontal border
	return (0);
}

int main(int argc, char *argv[])
{
	FILE *file;
	int width, height, x_index, y_index;
	char background, fill, id;
	float x, y, r_base, r_height;
	char **result;

	if (argc != 2)
		return (ft_error(ERR0));
	file = fopen(argv[1], "r");
	if (!file)
		return (ft_error(ERR1));
	if (fscanf(file, "%d %d %c\n", &width, &height, &background) != 3)
		return (ft_error(ERR1));
	if (width < 1 || width > 300 || height < 1 || height > 300)
		return (ft_error(ERR1));
	result = malloc(sizeof(char *) * height);
	result[height] = NULL;
	if (!result)
		return (ft_error(ERR1));
	y_index = -1;
	while (result[++y_index])
	{
		result[y_index] = malloc(sizeof(char) * width);
		memset(result[y_index], background, width);
		result[y_index][width] = '\0';
	}
	while (fscanf(file, "%c %f %f %f %f %c\n", &id, &x, &y, &r_base, &r_height, &fill) == 6)
	{
		printf("here\n");
		if (r_base <= 0.00000000 || r_height <= 0.00000000)
			return (ft_error(ERR1));
		y_index = -1;
		while (++y_index < height)
		{
			printf("cycling, y = %d\n", y_index);
			x_index = -1;
			while (++x_index < width)
			{
				printf("x = %d | width = %d\n", x_index, width);
				if (ft_check((int)x, (int)y, (int)r_height, (int)r_base, y_index, x_index) == 2
						|| ft_check((int)x, (int)y, (int)r_height, (int)r_base, y_index, x_index) == 3
						|| (ft_check((int)x, (int)y, (int)r_height, (int)r_base, y_index, x_index) == 1
							&& id == 'R'))
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
	ft_free_matrix(result);
	fclose(file);
	return (0);
}

