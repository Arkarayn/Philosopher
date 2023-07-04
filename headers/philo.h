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
# include <string.h>
# include <assert.h>
# include <string.h>
# include <pthread.h>

# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define RESET		"\033[0m"

struct	s_main;

typedef struct s_phils
{
	int				id;
	int				meals;
	bool			ate;
	long long		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*meal;
	pthread_mutex_t	*print;
	pthread_mutex_t	*stop_mtx;
	pthread_mutex_t	*mtx;
	pthread_mutex_t	*ate_mtx;
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
	pthread_mutex_t	stop_mtx;
	pthread_mutex_t	mtx;
	pthread_mutex_t	ate_mtx;
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
void	sleep_and_think(t_phils *philo);
void	death_by_star(t_main *main, int i);

#endif
