/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:21:08 by apesic            #+#    #+#             */
/*   Updated: 2025/06/20 10:26:19 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
		pthread_mutex_destroy(&rules->forks[i++]);
	free(rules->forks);
	free(rules->philos);
	pthread_mutex_destroy(&rules->print);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (init_rules(&rules, argc, argv) != 0)
		return (write_error("Init failed\n"));
	if (create_philosophers(&rules) != 0)
	{
		destroy_all(&rules);
		return (write_error("Philo creation failed\n"));
	}
	if (start_simulation(&rules) != 0)
	{
		destroy_all(&rules);
		return (write_error("Simulation error\n"));
	}
	destroy_all(&rules);
	return (0);
}
