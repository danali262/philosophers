#include "philo.h"

void	*routine(void	*arg)
{
	t_philo			*philosophers;

	philosophers = arg;
	picks_forks(philosophers);
	eats(philosophers);
	drops_forks(philosophers);
	sleeps(philosophers);
	thinks(philosophers);
	return (0);
}

int	create_threads(t_input *input, t_philo *philo)
{
	pthread_t	*philo_group;
	int			i;

	philo_group = malloc(sizeof(pthread_t) * input->n);
	if (!philo_group)
		return (-1);
	i = 0;
	while (i < input->n)
	{
		philo[i].index = i + 1;
		if (pthread_create(&philo_group[i], NULL, &routine, &philo[i]) != 0)
		{
			printf("Failed to create the threads\n");
			return (-1);
		}
		i++;
	}
	i = 0;
	while (i < input->n)
	{
		if (pthread_join(philo_group[i], NULL) != 0)
		{
			printf("Failed to join the threads\n");
			return (-1);
		}
		i++;
	}
	free(philo_group);
	return (0);
}
