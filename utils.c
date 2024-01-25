#include "philo.h"

long	get_current_time()
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	message_exit()
{
	printf("Please use the syntax below:\n");
	printf("./philo [number of philosophers] "
	"[time to die] [time to eat] [time to sleep]\n");
	printf("You can also add [number that each philosopher should eat]\n");
	printf("!!!And don't forget, giving natural numbers\n");
	return (EXIT_FAILURE);
}

int	message_exit_2()
{
	printf("There might be problem occurance when");
	printf(" try to initialize the threads\n");
	printf("! Or you can not allocate that area\n");
	return (EXIT_FAILURE);
}