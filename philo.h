/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:20:20 by apesic            #+#    #+#             */
/*   Updated: 2025/06/20 10:23:42 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_rules
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long long		start_time;
	int				died;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}					t_rules;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_rules			*rules;
}					t_philo;

int					init_rules(t_rules *rules, int argc, char **argv);
int					create_philosophers(t_rules *rules);
long				ft_atoi(const char *str);
size_t				ft_strlen(const char *str);
bool				check_neg(int argc, char **argv);
bool				check_str(int argc, char **argv);
int					write_error(const char *msg);
int					start_simulation(t_rules *rules);
void				*philo_routine(void *arg);
int					monitor(t_rules *rules);
void				print_action(t_rules *rules, int id, const char *msg);
long long			timestamp(void);

#endif
