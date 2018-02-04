/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_funk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 14:36:59 by afokin            #+#    #+#             */
/*   Updated: 2018/02/03 14:37:01 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void			img_pixel_put(t_image *data, int x, int y, int color)
{
	if (x >= WIN_W || y >= WIN_H || x < 0 || y < 0)
		return ;
	*(int *)(data->pix_ptr + ((x + y * WIN_W) * data->bit_pixel / 8)) = color;
}
