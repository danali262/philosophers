/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: danali <danali@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/06 16:09:37 by danali        #+#    #+#                 */
/*   Updated: 2021/09/06 16:12:23 by danali        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->n)
	{
		if (input->forks_status[i] == 1)
		{
			pthread_mutex_unlock(&input->forks[i]);
			input->forks_status[i] = 0;
		}
		i++;
	}
}

static void	*monitor_routine(void	*arg)
{
	t_philo				*philo;
	unsigned long long	difference;

	philo = arg;
	while (philo->input->dead_flag == 0 && philo->times_eaten
		!= philo->input->n_times_to_eat)
	{
		usleep(500);
		pthread_mutex_lock(&philo->input->dead_philo);
		difference = get_time() - philo->time_since_last_meal;
		if (difference > philo->input->time_to_die)
		{
			print_died(philo);
			unlock_forks(philo->input);
		}
		pthread_mutex_unlock(&philo->input->dead_philo);
	}
	return (0);
}

static void	routine_loop(t_philo *philo)
{
	if (philo->state == THINKING && philo->input->dead_flag == 0)
		picks_forks(philo);
	if (philo->state == EATING && philo->input->dead_flag == 0)
		eats(philo);
	if (philo->state == SLEEPING && philo->input->dead_flag == 0)
		sleeps(philo);
	if (philo->state == THINKING && philo->input->dead_flag == 0)
		thinks(philo);
}

void	*routine(void	*arg)
{
	t_philo			*philo;
	pthread_t		monitor;

	philo = arg;
	if (pthread_create(&monitor, NULL, monitor_routine, philo) != 0)
	{
		printf("Failed to create the threads\n");
		return (NULL);
	}
	philo->start_time = get_time();
	philo->time_since_last_meal = philo->start_time;
	while (philo->input->dead_flag == 0 && philo->times_eaten
		!= philo->input->n_times_to_eat)
		routine_loop(philo);
	if (pthread_join(monitor, NULL) != 0)
	{
		printf("Failed to join the threads\n");
		return (NULL);
	}
	return (0);
}
