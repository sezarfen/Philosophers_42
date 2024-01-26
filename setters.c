#include "philo.h"

t_philo	*set_philosopher(t_info *info, int id)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->info = info;
	philo->id = id + 1;
	philo->right_fork = &info->forks[id];
	philo->left_fork = &info->forks[(id + 1) % info->number_of_p];
	pthread_mutex_init(&(philo->eat_mutex), NULL);
	philo->last_eat = get_current_time();
	philo->eat_count = 0;
	return (philo);
}

int	set_info(t_info *info, int argc, char *argv[])
{
	info->number_of_p = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->eat_count_check = -1;
	info->each_philo_eat = -1;
	if (argc == 6)
	{
		info->eat_count_check = 1;
		info->each_philo_eat = ft_atoi(argv[5]);
	}
	info->time_start = get_current_time();
	if (pthread_mutex_init(&(info->print_mutex), NULL));
		return (0);
	info->philosophers = malloc(sizeof(t_philo *) * info->number_of_p);
    if (info->philosophers == NULL)
		return (0);
	return (1);
}
