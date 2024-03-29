/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:27:07 by fdundar           #+#    #+#             */
/*   Updated: 2024/01/27 00:27:07 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_checker(t_info *info, int count, int i)
{
	while (1)
	{
		pthread_mutex_lock(&(info->philosophers[i].eat_mutex));
		if (get_current_time() - info->philosophers[i].last_eat
			> info->time_to_die)
		{
			pthread_mutex_lock(&(info->print_mutex));
			return (printf("%ld %d died\n", gtp(info), i + 1), 1);
		}
		if (info->eat_count_check == 1
			&& info->philosophers[i].eat_count >= info->each_philo_eat)
			count += info->philosophers[i].eat_count;
		else
			count = 0;
		if (info->eat_count_check == 1
			&& count >= info->each_philo_eat * info->number_of_p)
			return (pthread_mutex_lock(&(info->print_mutex)), 2);
		pthread_mutex_unlock(&(info->philosophers[i].eat_mutex));
		i++;
		if (i >= info->number_of_p)
			i = 0;
	}
}

int	start_threads(t_info *info)
{
	int	i;

	i = 0;
	info->start_eating = 0;
	while (i < info->number_of_p)
	{
		set_philosopher(&(info->philosophers[i]), info, i);
		if (pthread_create(&(info->philo_threads[i]), NULL,
				life_of_philo, &(info->philosophers[i])))
			return (0);
		if (pthread_detach(info->philo_threads[i]) != 0)
			return (0);
		i++;
	}
	info->start_eating = 1;
	return (1);
}

int	allocate_threads_and_philos(t_info *info)
{
	int	i;

	i = 0;
	info->philo_threads = malloc(sizeof(pthread_t) * info->number_of_p);
	info->philosophers = malloc(sizeof(t_philo) * info->number_of_p);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_of_p);
	if (!info->philo_threads || !info->forks || !info->philosophers)
		return (0);
	while (i < info->number_of_p)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_info	info;

	if (argc != 5 && argc != 6)
		return (message_exit());
	if (!set_info(&info, argc, argv))
		return (message_exit_2());
	if (!check_info(&info))
		return (message_exit());
	if (!allocate_threads_and_philos(&info))
		return (free_all(&info), message_exit_2());
	if (!start_threads(&info))
		return (free_all(&info), message_exit_2());
	start_checker(&info, 0x000, 0b000);
	free_all(&info);
	return (EXIT_SUCCESS);
}
