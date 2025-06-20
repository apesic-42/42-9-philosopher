/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:21:01 by apesic            #+#    #+#             */
/*   Updated: 2025/06/20 10:26:48 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	print_action(t_rules *rules, int id, const char *msg)
{
	long long	time;

	pthread_mutex_lock(&rules->print);
	if (!rules->died)
	{
		time = timestamp() - rules->start_time;
		printf("%lld %d %s\n", time, id, msg);
	}
	pthread_mutex_unlock(&rules->print);
}
