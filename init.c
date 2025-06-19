#include "philo.h"

int	ft_atoi(const char *str)
{
	long	res = 0;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return ((int)res);
}
size_t	ft_strlen(const char *str)
{
	size_t	i = 0;

	while (str[i])
		i++;
	return (i);
}


int	write_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}

int	init_rules(t_rules *rules, int argc, char **argv)
{
	int i;

	i = 0;
	if (argc != 5 && argc != 6)
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
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	rules->philos = malloc(sizeof(t_philo) * rules->nb_philo);
	if (!rules->forks || !rules->philos)
		return (1);
	while (i < rules->nb_philo)
		pthread_mutex_init(&rules->forks[i++], NULL);
	pthread_mutex_init(&rules->print, NULL);
	return (0);
}

int	create_philosophers(t_rules *rules)
{
	int i;

	i = 0;
	while (i < rules->nb_philo)
	{
		t_philo *ph = &rules->philos[i];
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
