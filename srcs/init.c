/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:05:46 by gmattei           #+#    #+#             */
/*   Updated: 2023/06/15 17:05:48 by gmattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	init_fork(t_phils *philo)
{
	if (philo->id - 1 == philo->main->num)
	{
		philo->left_fork = &philo->main->forks[0];
		philo->right_fork = &philo->main->forks[philo->main->num - 1];
	}
	else
	{
		philo->left_fork = &philo->main->forks[philo->id - 1];
		philo->right_fork = &philo->main->forks[philo->id];
	}
}

int	mutex_init(t_main *main)
{
	int	i;

	if (pthread_mutex_init(&(main->meal), NULL))
		return (1);
	if (pthread_mutex_init(&(main->print), NULL))
		return (1);
	if (pthread_mutex_init(&(main->mtx), NULL))
		return (1);
	if (pthread_mutex_init(&(main->stop_mtx), NULL))
		return (1);
	if (pthread_mutex_init(&(main->mtx), NULL))
		return (1);
	i = -1;
	while (++i < main->num)
		if (pthread_mutex_init(&(main->forks[i]), NULL))
			return (1);
	return (0);
}

int	init_philo(t_main *main)
{
	main->i = main->num - 1;
	while (main->i >= 0)
	{
		main->phils[main->i].id = main->i + 1;
		main->phils[main->i].meals = 0;
		main->phils[main->i].ate = false;
		main->phils[main->i].last_meal = 0;
		main->phils[main->i].print = &main->print;
		main->phils[main->i].meal = &main->meal;
		main->phils[main->i].stop_mtx = &main->stop_mtx;
		main->phils[main->i].mtx = &main->mtx;
		main->phils[main->i].main = main;
		init_fork(&main->phils[main->i]);
		main->i--;
	}
	return (0);
}

void	init_struct(t_main *main, char **argv)
{
	main->num = ctm_atoi(main, argv[1]);
	main->phils = (t_phils *)malloc(sizeof(t_phils) * main->num);
	main->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) 
			* main->num);
	main->tdie = ctm_atoi(main, argv[2]);
	main->teat = ctm_atoi(main, argv[3]);
	main->tsleep = ctm_atoi(main, argv[4]);
	main->i = 0;
	main->all_ate = 0;
	main->first_timestamp = 0;
	main->stop = false;
}

int	init(t_main *main, char **argv)
{
	init_struct(main, argv);
	if (main->num < 1 || main->tdie < 0 || main->teat < 0 || main->tsleep < 0)
		return (err(2));
	if (argv[5])
	{
		main->mtodo = ctm_atoi(main, argv[5]);
		if (main->mtodo <= 0)
			return (err(2));
	}
	else
		main->mtodo = -1;
	if (mutex_init(main))
		return (err(3));
	if (init_philo(main) == -1)
		return (err(5));
	return (0);
}
