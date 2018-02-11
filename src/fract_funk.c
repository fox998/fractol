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

static int			get_num(t_complex z, t_complex c, int pres)
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

void	*maldelbort(void *param)
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
		c.r = 1.5 * (x + x - WIN_W) / (WIN_W * (*wind.rot)[3][3]) + (*wind.rot)[0][3];
		c.i = (y + y - WIN_H) / (WIN_H * (*wind.rot)[3][3]) + (*wind.rot)[1][3];
		img_pixel_put(wind.img, x, y, (get_num(c, c, 100)) * 0x01000F);
	}
	return (0);
}
