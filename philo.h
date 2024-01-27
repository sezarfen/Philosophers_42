/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:27:21 by fdundar           #+#    #+#             */
/*   Updated: 2024/01/27 00:27:21 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eat_mutex;
	long			last_eat;
	int				eat_count;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	long			number_of_p;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			eat_count_check;
	long			each_philo_eat;
	pthread_t		*philo_threads;
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	long			time_start;
	short			start_eating;
}	t_info;

// main.c
int		start_checker(t_info *info, int count, int i);
int		start_threads(t_info *info);
int		allocate_threads_and_philos(t_info *info);

// info.c
int		check_info(t_info *info);
int		set_info(t_info *info, int argc, char *argv[]);

// philosopher.c
void	eating_process(t_philo *philo);
void	sleeping_process(t_philo *philo);
void	thinking_process(t_philo *philo);
void	*life_of_philo(void *arg);
void	set_philosopher(t_philo *philo, t_info *info, int id);

// times.c
long	gtp(t_info *info);
long	get_current_time(void);

// utils.c
int		message_exit(void);
int		message_exit_2(void);
long	ft_atol(char *str);
void	ft_usleep(long ms);

#endif /* end of PHILO_H */