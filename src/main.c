/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:46:26 by afokin            #+#    #+#             */
/*   Updated: 2018/02/02 14:46:28 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void		init_matrix(t_rot_mat *rot)
{
	(*rot)[3][3] = 1;
	(*rot)[1][3] = 0;
	(*rot)[0][3] = -0.5;

}

void	*potok(void *param);

void print_fractl(t_window wind, t_rot_mat rot)
{
	t_complex	c;
	t_complex	z;
	double		temp;
	int			color;
	int y;
	int x;
	int num;



	int count_of_thread = 4;
	pthread_t 	tid[count_of_thread];
	y = 0;
	while (y < count_of_thread)
	{
		pthread_create(tid + y, NULL, potok, &wind);
		y++;
	}

	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
		{
			z.r = z.i = 0;
			c.r = 1.5 * (x + x - WIN_W) / (WIN_W * rot[3][3]) + rot[0][3];
			c.i = (y + y - WIN_H) / (WIN_H * rot[3][3]) + rot[1][3];
			num = 0;
			// z^2 + c = (Rz + Iz * i)^2 + Rc + Ic*i = Rz^2 + 2RzIz*i - Iz^2 + Rc + Ic*i
			// f(z) = u(Rz^2 - Iz^2 + Rc) + i * v(2RzIz + Ic);
			while (z.i * z.i + z.r * z.r < 4.0 && num < 500)
			{
				temp = z.r * z.r - z.i * z.i + c.r;
				z.i = 2 * z.r * z.i + c.i;
				z.r = temp;
				num++;
			}
			color = num * 0x01000F;
			img_pixel_put(wind.img, x, y, color);
		}
	}
	mlx_put_image_to_window(wind.mlx, wind.win, wind.img->img_ptr, 0, 0);
}

int main(void)
{
	t_window	wind;
	t_image		img;
	t_rot_mat	rot;

	wind.mlx = mlx_init();
	wind.win = mlx_new_window(wind.mlx, WIN_H, WIN_W, "fractol");
	wind.img = &img;
	img.img_ptr = mlx_new_image(wind.mlx, WIN_H, WIN_W);
	img.pix_ptr = mlx_get_data_addr(img.img_ptr, &img.bit_pixel,
		&img.line_size, &img.endian);
	init_matrix(&rot);
	wind.rot = &rot;
	print_fractl(wind, rot);

	mlx_expose_hook(wind.win, &expose_hook, &wind);
	mlx_mouse_hook(wind.win, &mouse_hook, &wind);
	mlx_key_hook(wind.win, &key_hook, &wind);
	mlx_loop(wind.mlx);
}
