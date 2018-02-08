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
	t_complex	c;
	int			x;
	int			y;
	t_thread	thread;
	t_window	wind;

	thread = *(t_thread*)param;
	wind = *thread.wind;
	y = thread.num * wind.line_per_thread + thread.y;
	x = -1;
	while (++x < WIN_W)
	{
		c.r = 1.5 * (x + x - WIN_W) / (WIN_W * (*wind.rot)[3][3]) + (*wind.rot)[0][3];
		c.i = (y + y - WIN_H) / (WIN_H * (*wind.rot)[3][3]) + (*wind.rot)[1][3];
		img_pixel_put(wind.img, x, y, (get_num(c, c, 100)) * 0x01000F);
	}
	return (0);
}

static void		clean_img(char *addr, int size, int bit_pixel)
{
	int x;

	x = 0;
	while (x < size)
	{
		*(int *)(addr + ((x) * bit_pixel / 8)) = 0xFFFFFF;
		x++;
	}
}

void print_fractl(t_window wind, t_rot_mat rot)
{
	int			num;
	int			y;
	t_thread	thread[NUM_OF_THREADS];

	for (int i = 0; i < NUM_OF_THREADS; i++)
	{
		thread[i].wind = &wind;
		thread[i].num = i;
	}
	y = -1;
	while (++y < wind.line_per_thread)
	{
		num = -1;
		while (++num < NUM_OF_THREADS)
		{
			thread[num].y = y;
			pthread_create(&thread[num].des, NULL, potok, thread + num);
		}
		while (num-- > 0)
			pthread_join(thread[num].des, NULL);
	}
	mlx_put_image_to_window(wind.mlx, wind.win, wind.img->img_ptr, 0, 0);
}

t_window	*wind_init(char *window_name)
{
	t_window	*wind;
	t_image		*img;
	t_rot_mat	*rot;

	wind = (t_window*)malloc(sizeof(t_window));
	rot = (t_rot_mat*)malloc(sizeof(t_rot_mat));
	img = (t_image*)malloc(sizeof(t_image));
	wind->mlx = mlx_init();
	wind->win = mlx_new_window(wind->mlx, WIN_W, WIN_H, window_name);
	wind->img = img;
	wind->line_per_thread = WIN_H / NUM_OF_THREADS;
	img->img_ptr = mlx_new_image(wind->mlx, WIN_W, WIN_H);
	img->pix_ptr = mlx_get_data_addr(img->img_ptr, &img->bit_pixel,
		&img->line_size, &img->endian);
	init_matrix(rot);
	wind->rot = rot;
	return(wind);
}

static void	get_window(t_window *wind, int pid)
{
	printf("1 %i\n", pid);
	print_fractl(*wind, *wind->rot);
	mlx_expose_hook(wind->win, &expose_hook, wind);
	mlx_mouse_hook(wind->win, &mouse_hook, wind);
	mlx_key_hook(wind->win, &key_hook, wind);
	printf("2 %i\n", pid);
	mlx_loop(wind->mlx);
}

int main(int argc, char **argv)
{
	int			i;
	t_window	**arr_wind;
	pid_t		pid;


	i = check_input(argc, argv);
	arr_wind = (t_window **)malloc(sizeof(t_window*) * 2);
	arr_wind[0] = i & 1 ? wind_init(argv[1]) : NULL;
	arr_wind[1] = (i << 1) & 1 ? wind_init(argv[2]) : NULL;


	pid = fork();
	printf("%i\n", pid);
	get_window(arr_wind[pid == 0 ? 1 : 0], pid);
	//get_window(arr_wind[pid == 0 ? 0 : 1]);
	// print_fractl(*arr_wind[0], *arr_wind[0]->rot);
	// mlx_expose_hook(arr_wind[0]->win, &expose_hook, arr_wind[0]);
	// mlx_mouse_hook(arr_wind[0]->win, &mouse_hook, arr_wind[0]);
	// mlx_key_hook(arr_wind[0]->win, &key_hook, arr_wind[0]);
	// mlx_loop(arr_wind[0]->mlx);
}
