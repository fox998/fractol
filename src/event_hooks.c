/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 16:52:14 by afokin            #+#    #+#             */
/*   Updated: 2018/02/04 16:52:16 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int		leave_hook(void *param)
{
	t_window	*wind;
	int			num;

	wind = (t_window*)param;
	num = --(*wind->num_of_wind);
	mlx_destroy_window(wind->mlx, wind->win);
	if (num == 0)
		exit(0);
	return (0);
}

int		mouse_move_hook(int x, int y, void *param)
{
	t_window	*wind;

	wind = (t_window*)param;
	if ((*wind->rot)[2][2])
	{
		(*wind->rot)[3][0] = (x + x - WIN_W) / (WIN_W * 1.0)
		+ (*wind->rot)[0][3];
		(*wind->rot)[3][1] = (y + y - WIN_H) / (WIN_H * 1.0)
		+ (*wind->rot)[1][3];
		print_fractl(*wind);
	}
	return (0);
}

int		mouse_hook(int but, int x, int y, void *param)
{
	t_window	*wind;

	wind = (t_window*)param;
	but == 1 ? (*wind->rot)[3][3] *= 1.2 : 0;
	but == 2 ? (*wind->rot)[3][3] *= 0.8 : 0;
	(*wind->rot)[0][3] = (x + x - WIN_W) / (WIN_W * (*wind->rot)[3][3])
	+ (*wind->rot)[0][3];
	(*wind->rot)[1][3] = (y + y - WIN_H) / (WIN_H * (*wind->rot)[3][3])
	+ (*wind->rot)[1][3];
	print_fractl(*wind);
	return (0);
}

int		key_hook(int key, void *param)
{
	t_window	*wind;
	double		move;

	wind = (t_window*)param;
	move = 0.1 / (*wind->rot)[3][3];
	key == ESC ? exit(0) : 0;
	key == SPASE ? (*wind->rot)[2][2] = 1 - (*wind->rot)[2][2] : 0;
	key == A_KEY ? (*wind->rot)[0][3] -= move : 0;
	key == D_KEY ? (*wind->rot)[0][3] += move : 0;
	key == W_KEY ? (*wind->rot)[1][3] -= move : 0;
	key == S_KEY ? (*wind->rot)[1][3] += move : 0;
	key == PLUS ? (*wind->rot)[3][3] *= 1.2 : 0;
	key == MINUS ? (*wind->rot)[3][3] *= 0.8 : 0;
	key == ONE && (*wind->rot)[0][0] < 500 ? (*wind->rot)[0][0] += 20 : 0;
	key == TWO && (*wind->rot)[0][0] > 1 ? (*wind->rot)[0][0] -= 20 : 0;
	key == RIGHT_ERROW ? (*wind->rot)[3][0] -= move : 0;
	key == LEFT_ERROW ? (*wind->rot)[3][0] += move : 0;
	key == DOWN_ERROW ? (*wind->rot)[3][1] -= move : 0;
	key == UP_ERROW ? (*wind->rot)[3][1] += move : 0;
	print_fractl(*wind);
	return (0);
}
