#include "philo.h"

void	unlock_forks(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->input->n)
	{
		if (philo->input->forks_debug[i] == 1)
		{
			pthread_mutex_unlock(&philo->input->forks[i]);
			philo->input->forks_debug[i] = 0;
		}
		i++;
	}
}

void *monitor_routine(void	*arg)
{
	t_philo				*philo;
	unsigned long long	timestamp;
	unsigned long long	difference;

	philo = arg;
	while (philo->input->dead_flag == 0 && philo->times_eaten != philo->input->n_times_to_eat)
	{
		// usleep(500);
		pthread_mutex_lock(&philo->input->dead_philo);
		difference = get_time() - philo->time_since_last_meal;
		timestamp = get_time() - philo->start_time;
		if (difference > philo->input->time_to_die)
		// if (difference > philo->input->time_to_die && philo->input->dead_flag == 0)
		{
			print_died(timestamp, philo);
			philo->input->dead_flag = 1;
			philo->state = DIED;
			// return (0);
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
	if (pthread_create(&monitor, NULL, &monitor_routine, philo) != 0)			/* understand this */
	{
		printf("Failed to create the threads\n");
		return (NULL);
	}
	philo->start_time = get_time();
	philo->time_since_last_meal = philo->start_time;
	while (philo->input->dead_flag == 0 && philo->times_eaten != philo->input->n_times_to_eat)
	{
		usleep(500);
		if (philo->state == WANTS_TO_EAT && philo->input->dead_flag == 0)
			picks_forks(philo);
		if (philo->state == EATING && philo->input->dead_flag == 0)
			eats(philo);
		if (philo->state == SLEEPING && philo->input->dead_flag == 0)
			sleeps(philo);
		if (philo->state == THINKING && philo->input->dead_flag == 0)
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

	philo_group = ft_calloc(input->n, sizeof(pthread_t));
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
