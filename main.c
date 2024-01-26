#include "philo.h"

int	start_checker(t_info *info)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (1)
	{
		if (get_current_time() - info->philosophers[i].last_eat
			> info->time_to_die)
			return (printf("%ld %d died", gtp(info), i), 1);
		if (info->eat_count_check == 1 && info->philosophers[i].eat_count >= info->each_philo_eat)
		{
			count += info->philosophers[i].eat_count;
		}
		else
		{
			count = 0;
		}
		if (info->eat_count_check == 1 && count >= info->each_philo_eat * info->number_of_p)
		{
			return (printf("Everybody eaten\n"), 2);
		}
		i++;
		if (i > info->number_of_p) // farklı bir şekilde de yapılabilir "%" ile mesela
			i = 0;
	}
}

void	*life_of_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->info->time_to_eat);
	while (1)
	{
		eating_process(philo);
		sleeping_process(philo);
		thinking_process(philo);
	}
}

int	start_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_p)
	{
		set_philosopher(&(info->philosophers[i]), info, i);
		if (pthread_create(&(info->philo_threads[i]), NULL, life_of_philo, &(info->philosophers[i])))
			return (0);
		if (pthread_detach(info->philo_threads[i]) != 0)
			return (0);
		i++;		
	}
	return (1);
}

int	allocate_threads(t_info *info)
{
	int i;

	i = 0;
	info->philo_threads = malloc(sizeof(pthread_t) * info->number_of_p);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_of_p);
	if (!info->philo_threads || !info->forks)
		return (0);
	while (i < info->number_of_p)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL) != 0)
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
	t_info	*info;
	
	info = malloc(sizeof(t_info));
	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	if (!set_info(info, argc, argv))
		return (message_exit_2());
	if (!check_info(info))
		return (message_exit());
	if (!allocate_threads(info))
		return (message_exit_2());
	if (!start_threads(info))
		return (message_exit_2());
	start_checker(info);
	return (EXIT_SUCCESS);
}
