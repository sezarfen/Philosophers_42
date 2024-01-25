#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_info
{
	int				number_of_p;
	int		 		time_to_die;
	int				time_to_eat;
	int			 	time_to_sleep;
	int				eat_count_check;
	int				each_philo_eat;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
}	t_info;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_eat;
	int				eat_count;
	t_info			*info;
}	t_philo;

int	message_exit();

#endif /* end of PHILO_H */