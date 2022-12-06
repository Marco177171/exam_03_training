#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define ERR1 "Error: Operation file corrupted\n"
#define ERR2 "Error: argument\n"

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

int ft_check(float x_index, float y_index, float x, float y, float r_base, float r_height)
{
	if (x_index - x < 1.00000000 && x_index - x + r_base < 1.00000000
			&& y_index - y < 1.00000000 && y_index - y + r_height < 1.00000000)
		return (1); //outline
	else if (x_index > (int)x && x_index < (int)x + (int)r_base && y_index > (int)y && y_index < (int)y + (int)r_height)
		return (2); //inner pixel
	return (0);
}

int main(int argc, char *argv[])
{
	FILE *file;
	int x_index, y_index, width, height;
	float x, y, r_base, r_height;
	char id, background, fill;
	char **result;

	if (argc != 2)
		return (ft_error(ERR2));
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
	while (++y_index < height)
	{
		result[y_index] = malloc(sizeof(char) * width);
		memset(result[y_index], background, width);
		result[y_index][width] = '\0';
	}
	while (fscanf(file, "%c %f %f %f %f %c\n", &id, &x, &y, &r_base, &r_height, &fill) == 6)
	{
		if (r_height <= 0.00000000 || r_base <= 0.00000000 || (id != 'R' && id != 'r'))
			return (ft_error(ERR1));
		y_index = -1;
		while (++y_index < height)
		{
			x_index = -1;
			while (++x_index < width)
			{
				if (ft_check((float)x_index, (float)y_index, x, y, r_base, r_height) == 1
						|| (ft_check((float)x_index, (float)y_index, x, y, r_base, r_height) == 2
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
	fclose(file);
	return (0);
}
