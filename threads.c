#include "philo.h"

void *monitor_routine(void	*arg)
{
	t_philo				*philosophers;
	unsigned long long	timestamp;

	philosophers = arg;
	timestamp = get_time() - philosophers->time_since_last_meal;
	if (timestamp > philosophers->input->time_to_die)
		philosophers->dead = 1;
	return (0);
}

void	*routine(void	*arg)
{
	t_philo			*philosophers;
	pthread_t		monitor;

	philosophers = arg;
	if (pthread_create(&monitor, NULL, &monitor_routine, &philosophers) != 0)
	{
		printf("Failed to create the threads\n");
		return (NULL);
	}
	while (philosophers->dead == 0 && philosophers->times_eaten != philosophers->input->n_times_to_eat)
	{
		philosophers->timestamp = get_time();
		picks_forks(philosophers);
		eats(philosophers);
		drops_forks(philosophers);
		sleeps(philosophers);
		thinks(philosophers);
	}
	if (pthread_join(monitor, NULL) != 0)
	{
		printf("Failed to join the threads\n");
		return (NULL);
	}
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
