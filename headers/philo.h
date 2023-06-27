/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:06:21 by gmattei           #+#    #+#             */
/*   Updated: 2023/06/15 17:06:23 by gmattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdio.h>
# include <assert.h>
# include <pthread.h>

struct	s_main;

typedef struct s_phils
{
	int				id;
	int				meals;
	bool			ate;
	long long		last_meal;
	int				left_fork_id;
	int				right_fork_id;
	pthread_t		thread_id;
	struct s_main	*main;
}	t_phils;

typedef struct s_main
{
	t_phils			*phils;
	int				num;
	int				tdie;
	int				teat;
	int				tsleep;
	int				mtodo;
	int				i;
	bool			all_ate;
	bool			stop;
	long long		first_timestamp;
	pthread_mutex_t	meal;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}	t_main;
/* Functions */
/* Error Managament */
int		err(int error);
/* Utils */
void	print(t_main *main, int timestamp, int k, char *c);
int		ctm_atoi(t_main *main, char *str);
int		get_time(t_main *main, bool firstime);
/* Init */
int		init(t_main *main, char **argv);
int		init_philo(t_main *main);
/* Philo */
int		philo(t_main *main);

#endif
