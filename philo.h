/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:20:20 by apesic            #+#    #+#             */
/*   Updated: 2025/06/19 11:31:05 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <pthread.h>
#include <sys/time.h>




typedef struct s_rules {
	int             nb_philo;
	int             time_to_die;
	int             time_to_eat;
	int             time_to_sleep;
	int             must_eat_count;  // optionnel
	long long       start_time;
	int             died;
	pthread_mutex_t print;
	pthread_mutex_t *forks;
	struct s_philo  *philos;
} t_rules;

typedef struct s_philo {
	int             id;
	int             meals_eaten;
	long long       last_meal;
	pthread_t       thread_id;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_rules         *rules;
} t_philo;

int	init_rules(t_rules *rules, int argc, char **argv);
int	create_philosophers(t_rules *rules);
int	ft_atoi(const char *str);
int	write_error(const char *msg);
int	start_simulation(t_rules *rules);
void	*philo_routine(void *arg);
int		monitor(t_rules *rules);

#endif
