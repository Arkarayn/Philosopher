/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:06:00 by gmattei           #+#    #+#             */
/*   Updated: 2023/06/15 17:06:01 by gmattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	print(t_main *main, int timestamp, int k, char *c)
{
	pthread_mutex_lock(&main->print);
	pthread_mutex_lock(&main->stop_mtx);
	if (main->stop)
	{
		pthread_mutex_unlock(&main->stop_mtx);
		pthread_mutex_unlock(&main->print);
		return ;
	}
	pthread_mutex_unlock(&main->stop_mtx);
	if (main->num == 1)
		k++;
	if (!ft_strcmp(c, "fork"))
		printf(GREEN"%d -  philo n.%d has taken a fork\n"RESET, timestamp, k);
	else if (!ft_strcmp(c, "eat"))
		printf(RED"%d -  philo n.%d is eating\n"RESET, timestamp, k);
	else if (!ft_strcmp(c, "sleep"))
		printf(MAGENTA"%d -  philo n.%d is sleeping\n"RESET, timestamp, k);
	else if (!ft_strcmp(c, "think"))
		printf(MAGENTA"%d -  philo n.%d is thinking\n"RESET, timestamp, k);
	else if (!ft_strcmp(c, "die"))
		printf(YELLOW"%d -  philo n.%d died\n"RESET, timestamp, k);
	pthread_mutex_unlock(&main->print);
}

int	ctm_atoi(t_main *main, char *str)
{
	size_t	res;

	main->i = 0;
	res = 0;
	while (str[main->i])
	{
		if (main->i == 0 && (str[main->i] == '-'))
			return (err(1));
		else if (main->i == 0 && (str[main->i] == '+'))
			main->i++;
		if (str[main->i] < '0' || str[main->i] > '9')
			return (err(2));
		main->i++;
	}
	main->i = 0;
	while (str[main->i])
	{
		res = res * 10 + str[main->i] - '0';
		main->i++;
	}
	return (res);
}

int	get_time(t_main *main, bool firstime)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (firstime == true)
		return (main->first_timestamp = t.tv_sec * 1000 + t.tv_usec / 1000);
	else
		return (t.tv_sec * 1000 + t.tv_usec / 1000 - main->first_timestamp);
}

void	death_by_star(t_main *main, int i)
{
	while (i < main->num)
	{
		pthread_mutex_lock(&main->stop_mtx);
		if (main->stop)
		{
			pthread_mutex_unlock(&main->stop_mtx);
			break ;
		}
		pthread_mutex_unlock(&main->stop_mtx);
		usleep(3000);
		pthread_mutex_lock(&main->meal);
		if (main->phils[i].last_meal != 0 && get_time(main, false) - \
			main->phils[i].last_meal > main->tdie)
		{
			pthread_mutex_lock(&main->print);
			printf("%d -  philo n.%d died\n", get_time(main, false), \
				main->phils[i].id);
			main->stop = true;
			pthread_mutex_unlock(&main->print);
		}
		pthread_mutex_unlock(&main->meal);
		i++;
	}
}
