#include "philo.h"

void	initialize_input(t_input *input)
{
	input->n = 0;
	input->time_to_die = 0;
	input->time_to_eat = 0;
	input->time_to_sleep = 0;
	input->n_times_to_eat = 0;
}

int	initialize_philosophers(t_input *input, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < input->n)
	{
		philo[i].input = malloc(sizeof(t_input));
		if (!philo[i].input)
			return (-1);
		philo[i].input = input;
		philo[i].index = i + 1;
		philo[i].state = THINKING;		/* to be reviewed */
		if (i != input->n - 1)
			philo[i].left_fork = philo[i].index;
		else
			philo[i].left_fork = 0;
		philo[i].right_fork = philo[i].index - 1;
		philo[i].timestamp = 0;
		i++;
	}
	return (0);
}

int	initialize_mutex(t_philo *philo)
{
	int	i;

	philo->input->forks = malloc(sizeof(pthread_mutex_t) * philo->input->n);
	if (!philo->input->forks)
		return (-1);
	i = 0;
	while (i < philo->input->n)
	{
		pthread_mutex_init(&philo->input->forks[i], NULL);
		i++;
	}
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
}
