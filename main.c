#include "philo.h"

void	*life_of_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		eating_process(philo);
		sleeping_process(philo);
		thinking_process(philo);
	}
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
		if (pthread_create(&(info->philos[i]), NULL, life_of_philo, p))
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
	printf("-1-1-1");
	if (set_info(&info, argc, argv))
		return (message_exit_2());
	printf("000");
	if (!check_info(&info))
		return (message_exit());
	printf("111");
	if (!allocate_threads(&info))
		return (message_exit_2());
	printf("222");
	if (!start_threads(&info))
		return (message_exit_2());
}