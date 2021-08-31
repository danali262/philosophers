#include "philo.h"

void *monitor_routine(void	*arg)
{
	t_philo				*philo;
	unsigned long long	timestamp;
	unsigned long long	difference;

	philo = arg;
	while (philo->input->dead_flag == 0 && philo->times_eaten != philo->input->n_times_to_eat)
	{
		pthread_mutex_lock(&philo->input->dead_philo);
		difference = get_time() - philo->time_since_last_meal;
		timestamp = get_time() - philo->start_time;
		if (difference > philo->input->time_to_die && philo->input->dead_flag == 0)
		{
			print_message(timestamp, philo, DIED);
			philo->input->dead_flag = 1;
		}
		pthread_mutex_unlock(&philo->input->dead_philo);
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
	while (philo->input->dead_flag == 0 && philo->times_eaten != philo->input->n_times_to_eat)
	{
		if (philo->state == WANTS_TO_EAT && philo->input->dead_flag == 0)
			picks_forks(philo);
		if (philo->state == EATS && philo->input->dead_flag == 0)
			eats(philo);
		if (philo->state == DONE_EATING && philo->input->dead_flag == 0)
			drops_forks(philo);
		if (philo->state == SLEEPS && philo->input->dead_flag == 0)
			sleeps(philo);
		if (philo->state == THINKS && philo->input->dead_flag == 0)
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
