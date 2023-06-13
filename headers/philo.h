#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h> 
# include <stdio.h>
# include <assert.h>
# include <pthread.h>


typedef struct s_phils
{
    size_t id; // id of the philosophers
    size_t meals; //meals done
}   t_phils;

typedef struct s_main
{
    t_phils *phils;
    size_t num; // number of philosophers
    size_t tdie; // time to die
    size_t teat; // time to eat
    size_t tsleep; // time to sleep
    size_t mtodo; // number of meals to do
    size_t i; // counter
}   t_main;

//Functions

int     err(int error);
void    init(t_main *main);

#endif