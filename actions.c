/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: danali <danali@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/06 15:47:52 by danali        #+#    #+#                 */
/*   Updated: 2021/09/06 16:03:20 by danali        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	picks_forks(t_philo *philo)
{
	if (philo->index % 2 == 1)
		picks_forks_odd(philo);
	else
		picks_forks_even(philo);
	philo->state = EATING;
}

void	eats(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->dead_philo);
	philo->time_since_last_meal = get_time();
	print_message(philo, EATING);
	pthread_mutex_unlock(&philo->input->dead_philo);
	regulated_usleep(philo->input->time_to_eat * 1000);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->input->forks[philo->left_fork]);
	if (philo->input->dead_flag == 0)
		philo->input->forks_status[philo->left_fork] = 0;
	pthread_mutex_unlock(&philo->input->forks[philo->right_fork]);
	if (philo->input->dead_flag == 0)
		philo->input->forks_status[philo->left_fork] = 0;
	philo->state = SLEEPING;
}

void	sleeps(t_philo *philo)
{
	print_message(philo, SLEEPING);
	regulated_usleep(philo->input->time_to_sleep * 1000);
	philo->state = THINKING;
}

void	thinks(t_philo *philo)
{
	print_message(philo, THINKING);
}
