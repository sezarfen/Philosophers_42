/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:27:34 by fdundar           #+#    #+#             */
/*   Updated: 2024/01/27 00:27:34 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	message_exit(void)
{
	printf("Please use the syntax below:\n");
	printf("./philo [number of philosophers] "
		"[time to die] [time to eat] [time to sleep]\n");
	printf("You can also add [number that each philosopher should eat]\n");
	printf("!!!And don't forget, giving natural numbers\n");
	return (EXIT_FAILURE);
}

int	message_exit_2(void)
{
	printf("There might be problem occurance when");
	printf(" try to initialize the threads\n");
	printf("! Or you can not allocate that area\n");
	return (EXIT_FAILURE);
}

int	ft_atoi(char *str)
{
	int	i;
	int	n;
	int	result;

	i = 0;
	n = 1;
	result = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
		result = (result * 10) + (str[i++] - 48);
	return (result * n);
}

void	ft_usleep(long ms)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(100);
}
