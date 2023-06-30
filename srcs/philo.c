/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:05:54 by gmattei           #+#    #+#             */
/*   Updated: 2023/06/15 17:05:55 by gmattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	philo_eat(t_phils *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print(philo->main, get_time(philo->main, false), philo->id, "fork");
	pthread_mutex_lock(philo->right_fork);
	print(philo->main, get_time(philo->main, false), philo->id, "fork");
	pthread_mutex_lock(philo->meal);
	print(philo->main, get_time(philo->main, false), philo->id, "eat");
	pthread_mutex_lock(philo->mtx);
	philo->last_meal = get_time(philo->main, false);
	pthread_mutex_unlock(philo->mtx);
	pthread_mutex_unlock(philo->meal);
	usleep(philo->main->teat * 1000);
	philo->meals++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *void_phils)
{
	t_phils	*philo;

	philo = (t_phils *)void_phils;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		philo_eat(philo);
		pthread_mutex_lock(philo->stop_mtx);
		if (philo->main->stop)
		{
			pthread_mutex_unlock(philo->stop_mtx);
			break ;
		}
		pthread_mutex_unlock(philo->stop_mtx);
		if (philo->main->all_ate)
			break ;
		print(philo->main, get_time(philo->main, false), philo->id, "sleep");
		usleep(philo->main->tsleep * 1000);
		print(philo->main, get_time(philo->main, false), philo->id, "think");
	}
	return (NULL);
}

void	finish(t_main *main)
{
	main->i = 0;
	while (main->i < main->num)
	{
		pthread_join(main->phils[main->i].thread_id, NULL);
		main->i++;
	}
	main->i = 0;
	pthread_mutex_destroy(&main->meal);
	while (main->i < main->num)
	{
		pthread_mutex_destroy(&main->forks[main->i]);
		main->i++;
	}
	pthread_mutex_destroy(&main->print);
	free(main->forks);
	free(main->phils);
	free(main);
}

void	death_check(t_main *main)
{
	int	i;

	while (!main->all_ate)
	{
		i = 0;
		death_by_star(main, i);
		pthread_mutex_lock(&main->stop_mtx);
		if (main->stop)
		{
			pthread_mutex_unlock(&main->stop_mtx);
			break ;
		}
		pthread_mutex_unlock(&main->stop_mtx);
		i = 0;
		while (i < main->num && main->mtodo != -1 && main->phils[i].meals \
			>= main->mtodo)
			i++;
		if (i == main->num)
			main->all_ate = true;
	}
}

int	philo(t_main *main)
{
	main->i = 0;
	main->first_timestamp = get_time(main, true);
	if (main->num == 1)
	{
		print(main, get_time(main, false), 0, "fork");
		usleep(main->tdie * 1000);
		print(main, get_time(main, false), 0, "die");
		return (0);
	}
	while (main->i < main->num)
	{
		if (pthread_create(&main->phils[main->i].thread_id, NULL, \
			philo_routine, &main->phils[main->i]))
			return (err(5));
		pthread_mutex_lock(&main->mtx);
		main->phils[main->i].last_meal = get_time(main, false);
		main->i++;
		pthread_mutex_unlock(&main->mtx);
	}
	death_check(main);
	finish(main);
	return (0);
}
