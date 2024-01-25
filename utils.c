#include "philo.h"

// get_time_passed
long	gtp(t_info *info)
{
	return (get_current_time() - info->time_start);
}

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

int	ft_atoi(char *str)
{
	int i;
	int n;
	int result;

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
		result = (result * 10) + (str[i] - 48);
	return (result * n);
}