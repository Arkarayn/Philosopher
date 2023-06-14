#include "../headers/philo.h"

int main(int argc, char **argv)
{
    t_main *main;

    if(argc != 5 && argc != 6)
        return(err(4));
    main = malloc(sizeof(t_main));
    if(!main)
        return(err(3));
    if(init(main, argv) != 0)
        return(-1);
    philo(main);
}