#include "philo.h"

void	initialize_input(t_input *input)
{
	input->n = 0;
	input->time_to_die = 0;
	input->time_to_eat = 0;
	input->time_to_sleep = 0;
	input->n_times_to_eat = -1;
	input->dead_flag = 0;
}

int	initialize_philosophers(t_input *input, t_philo *philo)
{
	int	i;

	input->forks_debug = ft_calloc(input->n, sizeof(int));
	if (!input->forks_debug)
		return (-1);
	i = 0;
	while (i < input->n)
	{
		input->forks_debug[i] = 0;
		philo[i].input = ft_calloc(1, sizeof(t_input));
		if (!philo[i].input)
			return (-1);
		philo[i].input = input;
		philo[i].index = i + 1;
		philo[i].state = WANTS_TO_EAT;
		if (i != input->n - 1)
			philo[i].left_fork = philo[i].index;
		else
			philo[i].left_fork = 0;
		philo[i].right_fork = philo[i].index - 1;
		philo[i].times_eaten = 0;
		philo[i].start_time = 0;
		philo[i].time_since_last_meal = 0;
		i++;
	}
	return (0);
}

int	initialize_mutex(t_philo *philo)
{
	int	i;

	philo->input->forks = ft_calloc(philo->input->n, sizeof(pthread_mutex_t));
	if (!philo->input->forks)
		return (-1);
	i = 0;
	while (i < philo->input->n)
	{
		pthread_mutex_init(&philo->input->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo->input->print, NULL);
	pthread_mutex_init(&philo->input->dead_philo, NULL);
	return (0);
}

void	destroy_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->input->n)
	{
		pthread_mutex_destroy(&philo->input->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->input->print);
	pthread_mutex_destroy(&philo->input->dead_philo);
}
