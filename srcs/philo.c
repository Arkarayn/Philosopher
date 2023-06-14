#include "../headers/philo.h"

void philo_eat(t_main *main)
{
    int i;

    i = 0;
    get_time(main, true);
    pthread_mutex_lock(&main->forks[main->phils[main->i].left_fork_id]);
    print(get_time(main, false), main->phils[main->i].id, "fork");
    pthread_mutex_lock(&main->forks[main->phils[main->i].right_fork_id]);
    print(get_time(main, false), main->phils[main->i].id, "fork");
    print(get_time(main, false), main->phils[main->i].id, "is eating");
    main->phils[main->i].last_meal = get_time(main, false);
    usleep(main->teat * 1000);
    main->phils[main->i].meals++;
    main->phils[main->i].ate = true;
    pthread_mutex_unlock(&main->forks[main->phils[main->i].left_fork_id]);
    pthread_mutex_unlock(&main->forks[main->phils[main->i].right_fork_id]);
    while(i < main->num)
        if(main->phils[i].ate == true)
            i++;
    if(i == main->num)
        main->mtodo--;
}

void philo(t_main *main)
{
    while(main->mtodo != 0)
    {
        if(main->phils[main->i].last_meal != 0 && get_time(main, false) - main->phils[main->i].last_meal > main->tdie)
        {
            print(get_time(main, false), main->phils[main->i].id, "died");
            break;
        }
        if(main->phils[main->i].ate == false)
            philo_eat(main);
        else
        {
            print(get_time(main, false), main->phils[main->i].id, "is sleeping");
            usleep(main->tsleep * 1000);
            print(get_time(main, false), main->phils[main->i].id, "is thinking");
        }
    }
}