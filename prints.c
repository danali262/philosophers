/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prints.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: danali <danali@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/06 15:47:34 by danali        #+#    #+#                 */
/*   Updated: 2021/09/06 15:47:37 by danali        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, int option)
{
	pthread_mutex_lock(&philo->input->print);
	if (philo->input->dead_flag == 1 || philo->times_eaten
		== philo->input->n_times_to_eat)
	{
		pthread_mutex_unlock(&philo->input->print);
		return ;
	}
	philo->timestamp = get_time() - philo->start_time;
	if (option == TAKEN_FORK)
		printf("%lld Philosopher %d has taken a fork.\n", philo->timestamp,
			philo->index);
	if (option == EATING)
		printf("%lld Philosopher %d is eating.\n", philo->timestamp,
			philo->index);
	if (option == SLEEPING)
		printf("%lld Philosopher %d is sleeping.\n", philo->timestamp,
			philo->index);
	if (option == THINKING)
		printf("%lld Philosopher %d is thinking.\n", philo->timestamp,
			philo->index);
	pthread_mutex_unlock(&philo->input->print);
}

void	print_died(t_philo *philo)
{
	if (philo->input->dead_flag == 1)
		return ;
	philo->input->dead_flag = 1;
	pthread_mutex_lock(&philo->input->print);
	philo->timestamp = get_time() - philo->start_time;
	printf("%lld Philosopher %d died.\n", philo->timestamp, philo->index);
	pthread_mutex_unlock(&philo->input->print);
}
