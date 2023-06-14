#include "../headers/philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((*(unsigned char *)s1 - *(unsigned char *)s2));
}

void print(int timestamp, int k, char *c)
{
    if(ft_strcmp(c, "fork"))
        printf("%d -  philo n.%d has taken a fork", timestamp, k);
    if(ft_strcmp(c, "eat"))
        printf("%d -  philo n.%d is eating", timestamp, k);
    if(ft_strcmp(c, "sleep"))
        printf("%d -  philo n.%d is sleeping", timestamp, k);
    if(ft_strcmp(c, "think"))
        printf("%d -  philo n.%d is thinking", timestamp, k);
    if(ft_strcmp(c, "die"))
        printf("%d -  philo n.%d died", timestamp, k);
}

int ctm_atoi(t_main *main, char *str)
{
    size_t res;

    main->i = 0;
    res = 0;
    while (str[main->i])
    {
        if(main->i == 0 && (str[main->i] == '-'))
            return (err(1));
        else if (main->i == 0 && (str[main->i] == '+'))
            main->i++;
        if (str[main->i] < '0' || str[main->i] > '9')
            return (err(2));
        main->i++;
    }
    main->i = 0;
    while(str[main->i])
    {
        res = res * 10 + str[main->i] - '0';
        main->i++;
    }
    return (res);
}

int get_time(t_main *main, bool firstime)
{
    struct timeval t;

    gettimeofday(&t, NULL);
    if(firstime == true )
        return(main->first_timestamp = t.tv_usec);
    else
        return(t.tv_usec - main->first_timestamp);
}