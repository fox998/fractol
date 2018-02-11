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

static void		init_matrix(t_rot_mat *rot)
{
	(*rot)[3][3] = 1;
	(*rot)[1][3] = 0;
	(*rot)[0][3] = -0.5;
}

void print_fractl(t_window wind, t_rot_mat rot)
{
	int			num;
	int			y;
	t_thread	thread[NUM_OF_THREADS];

	for (int i = 0; i < NUM_OF_THREADS; i++)
	{
		thread[i].y = &y;
		thread[i].wind = &wind;
		thread[i].num = i;
	}
	y = -1;
	while (++y < wind.line_per_thread)
	{
		num = -1;
		while (++num < NUM_OF_THREADS)
		{
			pthread_create(&thread[num].des, NULL, wind.fract_foo, thread + num);
		}
		while (num-- > 0)
			pthread_join(thread[num].des, NULL);
	}
	mlx_put_image_to_window(wind.mlx, wind.win, wind.img->img_ptr, 0, 0);
}

static t_window	*wind_init(char *window_name, void *mlx)
{
	t_window	*wind;
	t_image		*img;
	t_rot_mat	*rot;
	static int wind_num = 0;

	wind_num++;
	wind = (t_window*)malloc(sizeof(t_window));
	rot = (t_rot_mat*)malloc(sizeof(t_rot_mat));
	img = (t_image*)malloc(sizeof(t_image));
	wind->win = mlx_new_window(mlx, WIN_W, WIN_H, window_name);
	wind->img = img;
	wind->mlx = mlx;
	wind->line_per_thread = WIN_H / NUM_OF_THREADS;
	img->img_ptr = mlx_new_image(wind->mlx, WIN_W, WIN_H);
	img->pix_ptr = mlx_get_data_addr(img->img_ptr, &img->bit_pixel,
		&img->line_size, &img->endian);
	init_matrix(rot);
	wind->rot = rot;
	wind->num_of_wind = &wind_num;
	*window_name == 'M' ? wind->fract_foo = &maldelbort : 0;
	return(wind);
}

static void	get_window(t_window *wind)
{
	print_fractl(*wind, *wind->rot);
	mlx_hook(wind->win, MotionNotify, ButtonMotionMask , &mouse_move_hook, wind);
	mlx_hook(wind->win, DestroyNotify, LeaveWindowMask, &leave_hook, wind);
	mlx_hook(wind->win, ButtonPress, ButtonPressMask, &mouse_hook, wind);
	mlx_hook(wind->win, KeyPress, KeyPressMask, &key_hook, wind);
}

int main(int argc, char **argv)
{
	int			i;
	void		*mlx;
	t_window	*wind_arr[MAX_WIND_NUM];


	i = check_input(argc, argv);
	mlx = mlx_init();
	wind_arr[0] = i & 1 ? wind_init(argv[1], mlx) : NULL;
	wind_arr[1] = (i >> 1) & 1 ? wind_init(argv[2], mlx) : NULL;
	get_window(wind_arr[0]);
	get_window(wind_arr[1]);
	mlx_loop(mlx);
	return (0);
}
