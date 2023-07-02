/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:05:27 by gmattei           #+#    #+#             */
/*   Updated: 2023/06/15 17:05:29 by gmattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	main(int argc, char **argv)
{
	t_main	*main;

	if (argc != 5 && argc != 6)
		return (err(4));
	main = malloc(sizeof(t_main));
	memset(main, 0, sizeof(t_main));
	if (!main)
		return (err(3));
	if (init(main, argv) != 0)
		return (-1);
	philo(main);
}
