#include "philo.h"

void    eating_process(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    printf("%ld %d has taken a fork", gtp(philo->info));
    pthread_mutex_lock(philo->right_fork);
    printf("%ld %d has taken a fork", gtp(philo->info));
}