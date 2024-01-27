/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:27:23 by fdundar           #+#    #+#             */
/*   Updated: 2024/01/27 00:27:23 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating_process(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	printf("%ld %d has taken a fork\n", gtp(philo->info), philo->id);
	pthread_mutex_lock(philo->left_fork);
	printf("%ld %d has taken a fork\n", gtp(philo->info), philo->id);
	pthread_mutex_lock(&(philo->last_eat_mutex));
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(&(philo->last_eat_mutex));
	pthread_mutex_lock(&(philo->eat_mutex));
	philo->eat_count++;
	pthread_mutex_unlock(&(philo->eat_mutex));
	printf("%ld %d is eating\n", gtp(philo->info), philo->id);
	ft_usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleeping_process(t_philo *philo)
{
	printf("%ld %d is sleeping\n", gtp(philo->info), philo->id);
	ft_usleep(philo->info->time_to_sleep);
}

void	thinking_process(t_philo *philo)
{
	printf("%ld %d is thinking\n", gtp(philo->info), philo->id);
}

void	*life_of_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->info->start_eating == 0)
		;
	if (philo->id % 2 == 0)
		ft_usleep(philo->info->time_to_eat);
	while (1)
	{
		eating_process(philo);
		sleeping_process(philo);
		thinking_process(philo);
	}
}

void	set_philosopher(t_philo *philo, t_info *info, int id)
{
	philo->info = info;
	philo->id = id + 1;
	philo->right_fork = &(info->forks[id]);
	philo->left_fork = &(info->forks[(id + 1) % info->number_of_p]);
	pthread_mutex_init(&(philo->eat_mutex), NULL);
	pthread_mutex_init(&(philo->last_eat_mutex), NULL);
	philo->last_eat = get_current_time();
	philo->eat_count = 0;
}
