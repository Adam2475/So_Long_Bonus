/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:48:32 by adapassa          #+#    #+#             */
/*   Updated: 2024/02/06 19:38:12 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx_linux/mlx.h"


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_circle(t_data *data, int centerX, int centerY, int radius, int color) {
    int x = radius;
    int y = 0;
    int decisionOver2 = 1 - x; // Decision criterion divided by 2 evaluated at x=r, y=0

    while (y <= x) {
        my_mlx_pixel_put(data, x + centerX, y + centerY, color); // Octant 1
        my_mlx_pixel_put(data, y + centerX, x + centerY, color); // Octant 2
        my_mlx_pixel_put(data, -x + centerX, y + centerY, color); // Octant 4
        my_mlx_pixel_put(data, -y + centerX, x + centerY, color); // Octant 3
        my_mlx_pixel_put(data, -x + centerX, -y + centerY, color); // Octant 5
        my_mlx_pixel_put(data, -y + centerX, -x + centerY, color); // Octant 6
        my_mlx_pixel_put(data, x + centerX, -y + centerY, color); // Octant 7
        my_mlx_pixel_put(data, y + centerX, -x + centerY, color); // Octant 8
        y++;

        if (decisionOver2 <= 0) {
            decisionOver2 += 2 * y + 1; // Change in decision criterion for y -> y+1
        } else {
            x--;
            decisionOver2 += 2 * (y - x) + 1; // Change for y -> y+1, x -> x-1
        }
    }
}

int main(int ac, char **av)
{
    //if (ac != 2)
        // return wrong params
    //if (parse_map(av[1]) == 1)
        // return map error

    void	*mlx;
	void	*mlx_win;
	t_data	img;
	int i = 0;
	int y = 100;

	/*
	Calculate the memory offset: Before writing a pixel, 
	calculate its correct position in memory.
	This accounts for the actual layout of the image data in memory.
	*/
	//int offset = (y * line_length + x * (bits_per_pixel / 8));

	
    mlx = mlx_init();
	//img.img = mlx_new_image(mlx, 1920, 1080);
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");

	//Understand that mlx_pixel_put is slow:
	//Direct pixel manipulation with mlx_pixel_put 

	//Use images for efficient pixel manipulation: Instead of writing directly to the window, you'll draw on an "image" buffer.
	//Then, you'll display this image in the window, which is much faster.

	/*
	** After creating an image, we can call `mlx_get_data_addr`, we pass
	** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
	** then be set accordingly for the *current* data address.
	*/

	// where to put and size
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
							&img.endian);

	while (i < 100)
	{
		my_mlx_pixel_put(&img, 5, i, 0x00FF0000);
		my_mlx_pixel_put(&img, i, 5, 0x00FF0000); // Draws a red pixel at (5,5)
		my_mlx_pixel_put(&img, 100, i, 0x00FF0000);
		my_mlx_pixel_put(&img, i, 100, 0x00FF0000);
		my_mlx_pixel_put(&img, y, i, 0x00FF0000);
		my_mlx_pixel_put(&img, i, y, 0x00FF0000);
		i = i + 2;
		y--;
	}

	draw_circle(&img, 960, 540, 100, 0x00FF0000);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	
	mlx_loop(mlx);
    return (0);
}