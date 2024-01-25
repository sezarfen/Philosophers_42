#include "philo.h"

void	*life_of_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		// eating
		// sleep
		// think
	}
}

t_philo	*set_philosopher(t_info *info, int id)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->info = info;
	philo->id = id;
	philo->right_fork = &(info->forks[id]);
	philo->left_fork = &(info->forks[(id + 1) % info->number_of_p]);
	philo->last_eat = get_current_time();
	philo->eat_count = 0;
	return (philo);
}

int	start_threads(t_info *info)
{
	int		i;
	t_philo	*p;

	i = 0;
	while (i < info->number_of_p)
	{
		p = set_philosopher(info, i);
		if (!p)
			return (0);
		if (pthread_create(info->philos[i], NULL, life_of_philo, p))
			return (0);
		if (pthread_detach(info->philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	allocate_threads(t_info *info)
{
	int i;

	i = 0;
	info->philos = malloc(sizeof(pthread_t) * info->number_of_p);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_of_p);
	if (!info->philos || !info->forks)
		return (0);
	while (i < info->number_of_p)
	{
		if (!pthread_mutex_init(&(info->forks[i]), NULL))
			return (0);
		i++;
	}
	return (1);
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
}

int check_info(t_info *info)
{
	if (info->eat_count_check == 1 && info->each_philo_eat < 0)
		return (0);
	return (info->number_of_p > 0 && info->time_to_die > 0
		&& info->time_to_eat && info->time_to_sleep);
}

int main(int argc, char *argv[])
{
	t_info	info;

	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	if (set_info(&info, argc, argv))
		return (message_exit_2());
	if (!check_info(&info))
		return (message_exit());
	if (!allocate_threads(&info))
		return (message_exit_2());
	if (!start_threads(&info))
		return (message_exit_2());
}