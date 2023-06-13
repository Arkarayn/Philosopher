#include "../headers/philo.h"

// mutex
// thread

int ctm_is_digit(char *str)
{
    size_t i;

    i = 0;
    while (str[i])
    {
        if(i == 0 && (str[i] == '-'))
            return (err(1));
        else if (i == 0 && (str[i] == '+'))
            i++;
        if (str[i] < '0' || str[i] > '9')
            return (err(2));
        i++;
    }
    return (1);
}

int ctm_atoi(char *str)
{
    size_t i;
    size_t res;

    i = 0;
    res = 0;
    if (!ctm_is_digit(str))
        return (-1);
    while(str[i])
    {
        res = res * 10 + str[i] - '0';
        i++;
    }
    return (res);
}

void args_to_struct(t_main *main, char **str)
{
    main->num = ctm_atoi(str[1]);
    main->tdie = ctm_atoi(str[2]);
    main->teat = ctm_atoi(str[3]);
    main->tsleep = ctm_atoi(str[4]);
    main->mtodo = ctm_atoi(str[5]);
}

int main(int argc, char **argv)
{
    t_main *main;

    if(argc != 6)
        return(err(4));
    main = malloc(sizeof(t_main));
    if(!main)
        return(err(3));
    init(main);
}