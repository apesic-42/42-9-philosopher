


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



void	*philo_routine(void *arg)
{
	t_philo		*philo = (t_philo *)arg;
	t_rules		*rules = philo->rules;

	if (rules->nb_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(rules, philo->id, "has taken a fork");
		usleep(rules->time_to_die * 1000);
		print_action(rules, philo->id, "died");
		pthread_mutex_unlock(philo->left_fork);
		rules->died = 1;
		return (NULL);
	}

	if (philo->id % 2 == 0)
		usleep(500); // décalage léger pour éviter les deadlocks

    while (!rules->died)
    {
        // THINKING
        print_action(rules, philo->id, "is thinking");

        // PRENDRE LES FOURCHETTES
        pthread_mutex_lock(philo->left_fork);
        print_action(rules, philo->id, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_action(rules, philo->id, "has taken a fork");

        // MANGER
        pthread_mutex_lock(&rules->print);
        philo->last_meal = timestamp();
        pthread_mutex_unlock(&rules->print);

        print_action(rules, philo->id, "is eating");
        usleep(rules->time_to_eat * 1000);

        pthread_mutex_lock(&rules->print);
        philo->meals_eaten++;
        pthread_mutex_unlock(&rules->print);

        // REPOSER LES FOURCHETTES
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        // DORMIR
        print_action(rules, philo->id, "is sleeping");
        usleep(rules->time_to_sleep * 1000);
    }
	return (NULL);
}

int     monitor(t_rules *rules)
{
        int                             i;
        long long               now;
        int                             full;

        while (!rules->died)
        {
                i = 0;
                full = 0;
                while (i < rules->nb_philo)
                {
                        pthread_mutex_lock(&rules->print);
                        now = timestamp();
                        if ((now - rules->philos[i].last_meal) >= rules->time_to_die)
                        {
                                if (!rules->died)
                                {
                                        printf("%lld %d died\n", now - rules->start_time, rules->philos[i].id);
                                        rules->died = 1;
                                }
                                pthread_mutex_unlock(&rules->print);
                                return (1);
                        }
                        if (rules->must_eat_count != -1 &&
                                rules->philos[i].meals_eaten >= rules->must_eat_count)
                                full++;
                        pthread_mutex_unlock(&rules->print);
                        i++;
                }
                if (rules->must_eat_count != -1 && full == rules->nb_philo)
                {
                        rules->died = 1;
                        return (0);
                }
                usleep(1000);
        }
        return (0);
}






int	start_simulation(t_rules *rules)
{
	int	i;

	i = 0;
	rules->start_time = timestamp();
	while (i < rules->nb_philo)
	{
		rules->philos[i].last_meal = rules->start_time;
		if (pthread_create(&rules->philos[i].thread_id, NULL,
				&philo_routine, &rules->philos[i]) != 0)
			return (1);
		usleep(100);
		i++;
	}
	if (monitor(rules) != 0)
		return (1);
	i = 0;
	while (i < rules->nb_philo)
		pthread_join(rules->philos[i++].thread_id, NULL);
	return (0);
}

