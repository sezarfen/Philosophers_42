#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_eat;
	int				eat_count;
	pthread_mutex_t	eat_mutex;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int				number_of_p;
	int		 		time_to_die;
	int				time_to_eat;
	int			 	time_to_sleep;
	int				eat_count_check;
	int				each_philo_eat;
	pthread_t		*philo_threads;
	t_philo			**philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	long			time_start;
}	t_info;

// utils.c
long	get_current_time();
int		message_exit();
int		message_exit_2();
long	gtp(t_info *info);
int		ft_atoi(char *str);

//	processes.c
void    eating_process(t_philo *philo);
void	sleeping_process(t_philo *philo);
void    thinking_process(t_philo *philo);
void	ft_usleep(long ms);

// setters.c
t_philo	*set_philosopher(t_info *info, int id);
int		set_info(t_info *info, int argc, char *argv[]);

// main.c
int		start_checker(t_info *info);
void	*life_of_philo(void *arg);
int		start_threads(t_info *info);
int		allocate_threads(t_info *info);
int 	check_info(t_info *info);


#endif /* end of PHILO_H */