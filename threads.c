#include "philo.h"

void *monitor_routine(void	*arg)
{
	t_philo				*philo;
	unsigned long long	timestamp;

	philo = arg;
	while (philo->dead == 0 && philo->times_eaten != philo->input->n_times_to_eat)
	{
		// usleep(500);
		timestamp = get_time() - philo->time_since_last_meal;
		if (timestamp > philo->input->time_to_die)
		{
			printf("%lld Philosopher %d died.\n", timestamp, philo->index);
			philo->dead = 1;
		}
	}
	return (0);
}

void	*routine(void	*arg)
{
	t_philo			*philo;
	pthread_t		monitor;

	philo = arg;
	if (pthread_create(&monitor, NULL, monitor_routine, philo) != 0)			/* understand this */
	{
		printf("Failed to create the threads\n");
		return (NULL);
	}
	philo->start_time = get_time();
	philo->time_since_last_meal = philo->start_time;
	while (philo->dead == 0 && philo->times_eaten != philo->input->n_times_to_eat)
	{
		if (philo->state == WANTS_TO_EAT && philo->dead == 0)
			picks_forks(philo);
		if (philo->state == EATING && philo->dead == 0)
			eats(philo);
		if (philo->state == DONE_EATING && philo->dead == 0)
			drops_forks(philo);
		if (philo->state == SLEEPING && philo->dead == 0)
			sleeps(philo);
		if (philo->state == THINKING && philo->dead == 0)
			thinks(philo);
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
