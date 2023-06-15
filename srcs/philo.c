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

/* void philo_eat(t_main *main)
{
    int i;

    i = 0;
	pthread_mutex_lock(&main->forks[main->phils[main->i].left_fork_id]);
	print(main, get_time(main, false), main->phils[main->i].id, "fork");
	pthread_mutex_lock(&main->forks[main->phils[main->i].right_fork_id]);
	print(main, get_time(main, false), main->phils[main->i].id, "fork");
    print(main, get_time(main, false), main->phils[main->i].id, "eat");
    usleep(main->teat * 1000);
    main->phils[main->i].last_meal = get_time(main, false);
    main->phils[main->i].meals++;
    main->phils[main->i].ate = true;
    pthread_mutex_unlock(&main->forks[main->phils[main->i].left_fork_id]);
    pthread_mutex_unlock(&main->forks[main->phils[main->i].right_fork_id]);
    while(i < main->num)
	{
        if(main->phils[i].ate == true)
            i++;
		else
			break;
	}
    if(i == main->num)
        main->mtodo--;
	main->i--;
}

void philo(t_main *main)
{
	main->i = main->num;
	get_time(main, true);
    while(main->mtodo != 0)
    {
        if(main->phils[main->i].last_meal != 0 && get_time(main, false) - main->phils[main->i].last_meal > main->tdie)
        {
            print(main, get_time(main, false), main->phils[main->i].id, "died");
            break;
        }
        if(main->phils[main->i].ate == false)
            philo_eat(main);
        else
        {
            print(main, get_time(main, false), main->phils[main->i].id, "sleep");
            usleep(main->tsleep * 1000);
            print(main, get_time(main, false), main->phils[main->i].id, "think");
        }
    }
}
 */

void *philo_routine(void *void_main)
{
    t_main *main;

    main = (t_main *)void_main;
    if(main->num % 2)
        usleep(10000);
    while(!main->stop)
    {
        //philo_eat(main);
        if(main->all_ate)
            break;
        print(main, get_time(main, false), main->phils[main->i].id, "sleep");
        usleep(main->tsleep * 1000);
        print(main, get_time(main, false), main->phils[main->i].id, "think");
    }
    return(NULL);
}
void death_check(t_main *main)
{
    int i;

    while(!main->all_ate)
    {
        i = 0;
        while(i < main->num && !main->stop)
        {
            if(main->phils[i].last_meal != 0 && get_time(main, false) - main->phils[i].last_meal > main->tdie)
            {
                print(main, get_time(main, false), main->phils[i].id, "die");
                main->stop = true;
                break;
            }
            i++;
        }
        i = 0;
        while(i < main->num && main->mtodo != -1 && main->phils[i].meals >= main->mtodo)
            i++;
        if(i == main->num)
            main->all_ate = true;
    }
}

int philo(t_main *main)
{
    main->i = 0;
    main->first_timestamp = get_time(main, true);
    while(main->i < main->num)
    {
        if(pthread_create(&main->phils[main->i].thread_id, NULL, philo_routine, &main->phils[main->i]))
            return(err(5));
        main->phils[main->i].last_meal = get_time(main, false);
        main->i++;
    }
    return(0);
}