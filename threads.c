#include "philo.h"

void	*routine(void	*arg)
{
	t_philo	*data;
	int			i;
	// struct	timeval t1;
	// struct	timeval t2;
	// double	elapsed_time;

	data = arg;
	// elapsed_time = 0;
	// gettimeofday(&t1, NULL);
	// usleep(250);
	// gettimeofday(&t2, NULL);
	// elapsed_time = (t2.tv_sec = t1.tv_sec) * 1000.0;
	// elapsed_time += (t2.tv_usec - t1.tv_usec) / 1000.0; 
	// printf("%f Philosopher %d has taken a fork\n", elapsed_time, index);
	i = 0;
	while (i < 2)
	{
		pthread_mutex_lock(&data->fork);
		pthread_mutex_unlock(&data->fork);
		i++;
	}
	free(arg);
	return (0);
}

int	create_threads(t_input *input, t_philo *data)
{
	pthread_t	*philo_group;
	int			i;

	philo_group = malloc(sizeof(pthread_t) * input->n);
	if (!philo_group)
		return (-1);
	i = 0;
	while (i < input->n)
	{
		data->index = i + 1;
		if (pthread_create(&philo_group[i], NULL, &routine, data) != 0)
		{
			printf("Failed to create the threads\n");
			return (-1);
		}
		printf("Philosopher %d has started\n", data->index);
		i++;
	}
	i = 0;
	while (i < input->n)
	{
		if (pthread_join(philo_group[i], NULL) != 0)
		{
			printf("Failed to join the threads\n");
			return (0);
		}
		i++;
	}
	free(philo_group);
	return (0);
}