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

// static void	*f(void *param, int num)
// {
// 	//if (num == 0)
// 		return (((t_window *)param)->ror);

// }

int		expose_hook(void *param)
{
	printf("expose_hook\n");
	return (0);
}

int		mouse_hook(int but, int x, int y, void *param)
{
	printf("mouse_hook but : %i\n", but);
	return (0);
}

int		key_hook(int key, void *param)
{
	t_window	*wind;
	double move;

	//printf("key_hook %i\n", key );
	wind = (t_window*)param;
	move = 0.1 / (*wind->rot)[3][3];
	key == ESC ? exit(0) : 0;
	key == A_KEY ? (*wind->rot)[0][3] -= move : 0;
	key == D_KEY ? (*wind->rot)[0][3] += move : 0;
	key == W_KEY ? (*wind->rot)[1][3] -= move : 0;
	key == S_KEY ? (*wind->rot)[1][3] += move : 0;
	key == PLUS ? (*wind->rot)[3][3] *= 1.2 : 0;
	key == MINUS ? (*wind->rot)[3][3] *= 0.8 : 0;
	print_fractl(*wind, (*wind->rot));
	return (0);
}


