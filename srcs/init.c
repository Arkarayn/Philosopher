#include "../headers/philo.h"

void init(t_main *main)
{
    main->phils = malloc(sizeof(t_phils) * main->num);
}

void thread_init(t_main *main)
{
    pthread_t *phils;

    phils = malloc(sizeof(pthread_t) * main->num);
    while(main->i < main->num)
    {
        pthread_create(&phils[main->i], NULL, NULL, NULL);
        main->i++;
    }
}