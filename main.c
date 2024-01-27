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
		pthread_mutex_lock(&(info->philosophers[i].last_eat_mutex));
		if (get_current_time() - info->philosophers[i].last_eat
			> info->time_to_die)
			return (printf("%ld %d died\n", gtp(info), i), 1);
		pthread_mutex_unlock(&(info->philosophers[i].last_eat_mutex));
		pthread_mutex_lock(&(info->philosophers[i].eat_mutex));
		if (info->eat_count_check == 1
			&& info->philosophers[i].eat_count >= info->each_philo_eat)
			count += info->philosophers[i].eat_count;
		else
			count = 0;
		if (info->eat_count_check == 1
			&& count >= info->each_philo_eat * info->number_of_p)
			return (printf("Everybody eaten\n"), 2);
		pthread_mutex_unlock(&(info->philosophers[i].eat_mutex));
		i++; //2 philo varsa bu 2. döngüde değeri 1 olur ve 2ye artar
		if (i == info->number_of_p) //ama bu kontrol 2 > 2 true olmadığı için i'ye 0 atanmaz
			i = 0; //dolayısıyla 3. bir philosof varmış gibi kontrol yapılır
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

int	allocate_threads(t_info *info)
{
	int	i;

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

// #include <stdio.h>
int	main(int argc, char *argv[])
{
	t_info	info;

	// printf("%ld\n", get_current_time());
	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	if (!set_info(&info, argc, argv))
		return (message_exit_2());
	if (!check_info(&info))
		return (message_exit());
	if (!allocate_threads(&info))
		return (message_exit_2());
	if (!start_threads(&info))
		return (message_exit_2());
	start_checker(&info, 0000, 0000);
	return (EXIT_SUCCESS);
}
