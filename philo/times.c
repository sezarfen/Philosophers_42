/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:27:32 by fdundar           #+#    #+#             */
/*   Updated: 2024/01/27 00:27:32 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// get_time_passed
long	gtp(t_info *info)
{
	return (get_current_time() - info->time_start);
}

long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
