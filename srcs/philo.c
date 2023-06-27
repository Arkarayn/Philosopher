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

void philo_eat(t_phils *philo)
{
    pthread_mutex_lock(&philo->main->forks[philo->left_fork_id]);
    print(philo->main, get_time(philo->main, false), philo->id, "fork");
    pthread_mutex_lock(&philo->main->forks[philo->right_fork_id]);
    print(philo->main, get_time(philo->main, false), philo->id, "fork");
    pthread_mutex_lock(&philo->main->meal);
    print(philo->main, get_time(philo->main, false), philo->id, "eat");
    philo->last_meal = get_time(philo->main, false);
    pthread_mutex_unlock(&philo->main->meal);
    usleep(philo->main->teat * 1000);
    philo->meals++;
    pthread_mutex_unlock(&philo->main->forks[philo->left_fork_id]);
    pthread_mutex_unlock(&philo->main->forks[philo->right_fork_id]);
}

void *philo_routine(void *void_phils)
{
    t_phils *philo;

    philo = (t_phils *)void_phils;
    if (philo->id % 2 == 0)
        usleep(1000);
    while (!philo->main->stop)
    {
        philo_eat(philo);
        if (philo->main->all_ate)
            break;
        print(philo->main, get_time(philo->main, false), philo->id, "sleep");
        usleep(philo->main->tsleep * 1000);
        print(philo->main, get_time(philo->main, false), philo->id, "think");
    }
    return (NULL);
}

void finish(t_main *main)
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
    pthread_mutex_unlock(&main->print);
	pthread_mutex_destroy(&main->print);
    free(main->forks);
    free(main->phils);
    free(main);
}
void death_check(t_main *main)
{
    int i;

    while (!main->all_ate && !main->stop)
    {
        i = 0;
        while (i < main->num && !main->stop)
        {
            usleep(10000);
            pthread_mutex_lock(&main->meal);
            if (main->phils[i].last_meal != 0 && get_time(main, false) - main->phils[i].last_meal > main->tdie)
            {
                pthread_mutex_lock(&main->print);
                printf("%d -  philo n.%d died\n", get_time(main, false), main->phils[i].id);
                main->stop = true;
            }
            pthread_mutex_unlock(&main->meal);
            i++;
        }
        if (main->stop)
            break;
        i = 0;
        while (i < main->num && main->mtodo != -1 && main->phils[i].meals >= main->mtodo)
            i++;
        if (i == main->num)
            main->all_ate = true;
    }
}

int philo(t_main *main)
{
    main->i = 0;
    main->first_timestamp = get_time(main, true);
    if(main->num == 1)
    {
        print(main, get_time(main, false), 0, "fork");
        usleep(main->tdie * 1000);
        print(main, get_time(main, false), 0, "die");
        return (0);
    }
    while (main->i < main->num)
    {
        if (pthread_create(&main->phils[main->i].thread_id, NULL, philo_routine, &main->phils[main->i]))
            return (err(5));
        main->phils[main->i].last_meal = get_time(main, false);
        main->i++;
    }
    death_check(main);
    finish(main);
    return (0);
}
