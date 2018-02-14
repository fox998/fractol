/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_funk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:12:57 by afokin            #+#    #+#             */
/*   Updated: 2018/02/11 20:13:01 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

static	int			t_num(t_complex z, t_complex c, int pres)
{
	double		temp;
	int			num;

	num = 0;
	while (z.i * z.i + z.r * z.r < 4.0 && num++ < pres)
	{
		temp = fabs(z.r * z.r - z.i * z.i - c.r);
		z.i = fabs(2 * z.r * z.i - c.i);
		z.r = temp;
	}
	return (num);
}

void				*t(void *param)
{
	t_complex	c;
	t_complex	z;
	int			xy[2];
	t_thread	thread;
	t_window	wind;

	thread = *(t_thread*)param;
	wind = *thread.wind;
	c.r = (*wind.rot)[3][0];
	c.i = (*wind.rot)[3][1];
	xy[1] = thread.num * wind.line_per_thread + *thread.y;
	xy[0] = -1;
	while (++xy[0] < WIN_W)
	{
		z.r = 1.5 * (xy[0] + xy[0] - WIN_W) /
		(WIN_W * (*wind.rot)[3][3]) + (*wind.rot)[0][3];
		z.i = (xy[1] + xy[1] - WIN_H) /
		(WIN_H * (*wind.rot)[3][3]) + (*wind.rot)[1][3];
		img_pixel_put(wind.img, xy[0],
			xy[1], (t_num(z, c, (*wind.rot)[0][0])) * 0x01000F);
	}
	return (0);
}

static	int			f_num(t_complex z, t_complex c, int pres)
{
	int			num;
	double		rsqr;
	double		isqrt;
	double		temp;

	num = 0;
	rsqr = z.r * z.r;
	isqrt = z.i * z.i;
	while (rsqr + isqrt < 4.0 && num++ < pres)
	{
		temp = rsqr - isqrt + (c.r * z.r + z.i * c.i) / (rsqr + isqrt);
		z.i = ((z.r * z.i) * 2) + (z.r * c.i - c.r * z.i) / (rsqr + isqrt);
		z.r = temp;
		rsqr = z.r * z.r;
		isqrt = z.i * z.i;
	}
	return (num);
}

void				*f(void *param)
{
	int			xy[2];
	t_thread	thread;
	t_window	wind;
	t_complex	z1;
	t_complex	c1;

	thread = *(t_thread*)param;
	wind = *thread.wind;
	c1.r = (*wind.rot)[3][0];
	c1.i = (*wind.rot)[3][1];
	xy[1] = thread.num * wind.line_per_thread + *thread.y;
	xy[0] = -1;
	while (++xy[0] < WIN_W)
	{
		z1.r = 1.5 * (xy[0] + xy[0] - WIN_W) /
		(WIN_W * (*wind.rot)[3][3]) + (*wind.rot)[0][3];
		z1.i = ((xy[1] + xy[1] - WIN_H) /
		(WIN_H * (*wind.rot)[3][3]) + (*wind.rot)[1][3]);
		img_pixel_put(wind.img, xy[0], xy[1],
			(f_num(z1, c1, (*wind.rot)[0][0])) * 0x0F00F);
	}
	return (0);
}
