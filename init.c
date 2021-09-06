/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: danali <danali@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/06 15:24:40 by danali        #+#    #+#                 */
/*   Updated: 2021/09/06 16:16:15 by danali        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

void	initialize_philosophers(t_input *input, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < input->n)
	{
		input->forks_status[i] = 0;
		philo[i].input = input;
		philo[i].index = i + 1;
		if (i != input->n - 1)
			philo[i].left_fork = philo[i].index;
		else
			philo[i].left_fork = 0;
		philo[i].right_fork = philo[i].index - 1;
		philo[i].times_eaten = 0;
		philo[i].state = THINKING;
		philo[i].start_time = 0;
		philo[i].timestamp = 0;
		philo[i].time_since_last_meal = 0;
		i++;
	}
}

static int	mutex_loop(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->n)
	{
		input->forks_status[i] = 0;
		if (pthread_mutex_init(&input->forks[i], NULL))
		{
			free(input->forks);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	initialize_mutex(t_input *input)
{
	input->forks = ft_calloc(input->n, sizeof(pthread_mutex_t));
	if (!input->forks)
		return (-1);
	input->forks_status = ft_calloc(input->n, sizeof(int));
	if (!input->forks_status)
		return (-1);
	if (mutex_loop(input) == -1)
		return (-1);
	if (pthread_mutex_init(&input->print, NULL)
		|| pthread_mutex_init(&input->dead_philo, NULL))
	{
		free(input->forks);
		return (-1);
	}
	return (0);
}

void	destroy_mutex(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->n)
	{
		pthread_mutex_destroy(&input->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&input->print);
	pthread_mutex_destroy(&input->dead_philo);
}
