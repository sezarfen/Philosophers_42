#include "philo.h"

void	ft_usleep(long ms)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < ms)
		usleep(100);
}

void    eating_process(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    printf("%ld %d has taken a fork\n", gtp(philo->info), philo->id);
    pthread_mutex_lock(philo->right_fork);
    printf("%ld %d has taken a fork\n", gtp(philo->info), philo->id);
    philo->last_eat = get_current_time();
    pthread_mutex_lock(&(philo->eat_mutex));
    philo->eat_count++;
    pthread_mutex_unlock(&(philo->eat_mutex));
    printf("%ld %d is eating\n", gtp(philo->info), philo->id);
    ft_usleep(philo->info->time_to_eat);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void    sleeping_process(t_philo *philo)
{
    printf("%ld %d is sleeping\n", gtp(philo->info), philo->id);
    ft_usleep(philo->info->time_to_sleep);
}

void    thinking_process(t_philo *philo)
{
    printf("%ld %d is thinking\n", gtp(philo->info), philo->id);
}