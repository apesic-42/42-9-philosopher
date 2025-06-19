#include "philo.h"

long	ft_atoi(const char *str)
{
	long	res;
	int		sign;
	int		i;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (2147483648);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
		if ((res > INT_MAX && sign == 1) || (res > (2147483648) && sign == -1))
			return (2147483648);
	}
	if (str[i])
		return (2147483648);
	return (res * sign);
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

bool check_neg(int argc, char **argv)
{
	int i;

	i = 1;
	while(i < argc)
	{
		if (ft_atoi(argv[i]) < 0)
			return (false);
		i++;
	}
	return (true);
}


bool	check_str(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '+')
			j++;
		if (argv[i][j] == '\0')
			return (false);
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}


int	init_rules(t_rules *rules, int argc, char **argv)
{
	int i;

	i = 0;
	if ((argc != 5 && argc != 6) || !check_str(argc, argv) || !check_neg(argc, argv))
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
