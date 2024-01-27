/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:26:34 by fdundar           #+#    #+#             */
/*   Updated: 2024/01/27 00:26:34 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_info(t_info *info)
{
	if (info->eat_count_check == 1 && info->each_philo_eat < 0)
		return (0);
	return (info->number_of_p > 0 && info->time_to_die > 0
		&& info->time_to_eat && info->time_to_sleep);
}

int	set_info(t_info *info, int argc, char *argv[])
{
	info->number_of_p = ft_atol(argv[1]);
	info->time_to_die = ft_atol(argv[2]);
	info->time_to_eat = ft_atol(argv[3]);
	info->time_to_sleep = ft_atol(argv[4]);
	info->eat_count_check = -1;
	info->each_philo_eat = -1;
	if (argc == 6)
	{
		info->eat_count_check = 1;
		info->each_philo_eat = ft_atol(argv[5]);
	}
	info->time_start = get_current_time();
	if (pthread_mutex_init(&(info->print_mutex), NULL) != 0)
		return (0);
	if (info->number_of_p < 0)
		return (0);
	info->philosophers = malloc(sizeof(t_philo) * info->number_of_p);
	if (info->philosophers == NULL)
		return (0);
	return (1);
}
