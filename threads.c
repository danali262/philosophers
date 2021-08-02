#include "philo.h"

void	*routine(void	*arg)
{
	int	index;
	struct	timeval t1;
	struct	timeval t2;
	double	elapsed_time;

	index = *(int *)arg;
	elapsed_time = 0;
	gettimeofday(&t1, NULL);
	usleep(250);
	gettimeofday(&t2, NULL);
	// elapsed_time = (t2.tv_sec = t1.tv_sec) * 1000.0;
	elapsed_time += (t2.tv_usec - t1.tv_usec) / 1000.0; 
	// printf("%g Philosopher %d has taken a fork\n", elapsed_time, index);
	printf("%f Philosopher %d has taken a fork\n", elapsed_time, index);
	free(arg);
	return (0);
}

int	create_threads(t_philo *options)
{
	pthread_t	*philo_group;
	int			i;
	int			*a;

	philo_group = malloc(sizeof(pthread_t) * options->n);
	i = 0;
	while (i < options->n)
	{
		a = malloc(sizeof(int));
		*a = i + 1;
		if (pthread_create(&philo_group[i], NULL, &routine, a) != 0)
		{
			printf("Failed to create the threads\n");
			return (-1);
		}
		printf("Philosopher %d has started\n", *a);
		i++;
	}
	i = 0;
	while (i < options->n)
	{
		if (pthread_join(philo_group[i], NULL) != 0)
		{
			printf("Failed to join the threads\n");
			return (0);
		}
		i++;
	}
	return (0);
}