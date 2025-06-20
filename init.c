/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:20:57 by apesic            #+#    #+#             */
/*   Updated: 2025/06/20 10:22:38 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_args(t_rules *rules, int argc, char **argv)
{
	if ((argc != 5 && argc != 6) || !check_str(argc, argv) || !check_neg(argc,
			argv))
		return (1);
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->must_eat_count = ft_atoi(argv[5]);
	else
		rules->must_eat_count = -1;
	rules->died = 0;
	if (rules->nb_philo <= 0 || rules->nb_philo > 200)
		return (1);
	return (0);
}

static int	init_structs(t_rules *rules)
{
	int	i;

	i = 0;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	rules->philos = malloc(sizeof(t_philo) * rules->nb_philo);
	if (!rules->forks || !rules->philos)
	{
		free(rules->forks);
		free(rules->philos);
		return (1);
	}
	while (i < rules->nb_philo)
		pthread_mutex_init(&rules->forks[i++], NULL);
	pthread_mutex_init(&rules->print, NULL);
	return (0);
}

int	init_rules(t_rules *rules, int argc, char **argv)
{
	if (init_args(rules, argc, argv) || init_structs(rules))
		return (1);
	return (0);
}

int	create_philosophers(t_rules *rules)
{
	int		i;
	t_philo	*ph;

	i = 0;
	while (i < rules->nb_philo)
	{
		ph = &rules->philos[i];
		ph->id = i + 1;
		ph->meals_eaten = 0;
		ph->rules = rules;
		ph->last_meal = 0;
		ph->left_fork = &rules->forks[i];
		ph->right_fork = &rules->forks[(i + 1) % rules->nb_philo];
		i++;
	}
	return (0);
}
