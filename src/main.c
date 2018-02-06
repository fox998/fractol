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

int			get_num(t_complex z, t_complex c, int pres)
{
	double		temp;
	int			num;

	// z^2 + c = (Rz + Iz * i)^2 + Rc + Ic*i = Rz^2 + 2RzIz*i - Iz^2 + Rc + Ic*i
	// f(z) = u(Rz^2 - Iz^2 + Rc) + i * v(2RzIz + Ic);
	num = 0;
	while (z.i * z.i + z.r * z.r < 4.0 && num++ < pres)
	{
		temp = z.r * z.r - z.i * z.i + c.r;
		z.i = 2 * z.r * z.i + c.i;
		z.r = temp;
	}
	return (num);
}

void	*potok(void *param)
{
	static int	thread = -1;
	t_complex	c;
	int			x;
	int			y;
	t_window	wind;

	wind = *(t_window*)param;
	thread = (thread + 1) % NUM_OF_THREADS;
	y = thread * wind.line_per_thread + wind.y;
	while (++x < WIN_W)
	{
		c.r = 1.5 * (x + x - WIN_W) / (WIN_W * (*wind.rot)[3][3]) + (*wind.rot)[0][3];
		c.i = (y + y - WIN_H) / (WIN_H * (*wind.rot)[3][3]) + (*wind.rot)[1][3];
		img_pixel_put(wind.img, x, y, get_num(c, c, 100) * 0x01000F);
	}
	return (0);
}

void print_fractl(t_window wind, t_rot_mat rot)
{
	int			num;
	pthread_t 	tid[NUM_OF_THREADS];

	wind.y = -1;
	while (++wind.y < wind.line_per_thread)
	{
		num = 0;
		while (num < NUM_OF_THREADS)
		{
			pthread_create(tid + num, NULL, potok, &wind);
			num++;
		}
		while (num > 0)
		{
			num--;
			pthread_join(tid[num], NULL);
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
	wind.line_per_thread = WIN_H / NUM_OF_THREADS;
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
