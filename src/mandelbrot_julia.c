/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_julia.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 17:19:43 by afokin            #+#    #+#             */
/*   Updated: 2018/02/14 17:19:45 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

static int			get_num(t_complex z, t_complex c, int pres)
{
	double		temp;
	int			num;

	num = 0;
	while (z.i * z.i + z.r * z.r < 4.0 && num++ < pres)
	{
		temp = z.r * z.r - z.i * z.i + c.r;
		z.i = 2 * z.r * z.i + c.i;
		z.r = temp;
	}
	return (num);
}

void				*maldelbort(void *param)
{
	t_complex	c;
	int			x;
	int			y;
	t_thread	thread;
	t_window	wind;

	thread = *(t_thread*)param;
	wind = *thread.wind;
	y = thread.num * wind.line_per_thread + *thread.y;
	x = -1;
	while (++x < WIN_W)
	{
		c.r = 1.5 * (x + x - WIN_W) /
		(WIN_W * (*wind.rot)[3][3]) + (*wind.rot)[0][3];
		c.i = (y + y - WIN_H) / (WIN_H * (*wind.rot)[3][3]) + (*wind.rot)[1][3];
		img_pixel_put(wind.img, x, y,
			(get_num(c, c, (*wind.rot)[0][0])) * 0x01000F);
	}
	return (0);
}

void				*julia(void *param)
{
	t_complex	c;
	t_complex	z;
	int			xy[2];
	t_thread	thread;
	t_window	wind;

	thread = *(t_thread*)param;
	wind = *thread.wind;
	xy[1] = thread.num * wind.line_per_thread + *thread.y;
	xy[0] = -1;
	c.r += (*wind.rot)[3][0];
	c.i += (*wind.rot)[3][1];
	while (++xy[0] < WIN_W)
	{
		z.r = 1.5 * (xy[0] + xy[0] - WIN_W) /
		(WIN_W * (*wind.rot)[3][3]) + (*wind.rot)[0][3];
		z.i = (xy[1] + xy[1] - WIN_H) /
		(WIN_H * (*wind.rot)[3][3]) + (*wind.rot)[1][3];
		img_pixel_put(wind.img, xy[0],
			xy[1], (get_num(z, c, (*wind.rot)[0][0])) * 0x01000F);
	}
	return (0);
}
