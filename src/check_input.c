/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:17:01 by afokin            #+#    #+#             */
/*   Updated: 2018/02/07 16:18:35 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../inc/fractol.h"

static int	ft_strcmp(const char *st1, const char *st2)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)st1;
	s2 = (unsigned char *)st2;
	while (*s1 == *s2 && *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

static void	usage(void)
{
	write(1, "usage: ./fractol fractol_name\nnames:", 36);
	write(1, "\n\tMandelbort\n\tJulia\n\tT\n\tF\n", 26);
	exit(1);
}

int			check_input(int argc, char **argv)
{
	int		i;
	int		res;

	if (argc != 2 && argc != 3)
		usage();
	res = 0;
	i = 0;
	while (++i < argc)
		if (!ft_strcmp(argv[i], "Mandelbort") || !ft_strcmp(argv[i], "Julia")
			|| !ft_strcmp(argv[i], "T") || !ft_strcmp(argv[i], "F"))
			res += pow(2, i - 1);
	if (res == 0)
		usage();
	return (res);
}
