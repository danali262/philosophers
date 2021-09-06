/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_aux.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: danali <danali@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/06 16:00:05 by danali        #+#    #+#                 */
/*   Updated: 2021/09/06 16:01:35 by danali        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	picks_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->forks[philo->right_fork]);
	if (philo->input->dead_flag == 0)
	{
		philo->input->forks_status[philo->right_fork] = 1;
		print_message(philo, TAKEN_FORK);
	}
	pthread_mutex_lock(&philo->input->forks[philo->left_fork]);
	if (philo->input->dead_flag == 0)
	{
		philo->input->forks_status[philo->left_fork] = 1;
		print_message(philo, TAKEN_FORK);
	}
}

static void	picks_forks_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->forks[philo->left_fork]);
	if (philo->input->dead_flag == 0)
	{
		philo->input->forks_status[philo->left_fork] = 1;
		print_message(philo, TAKEN_FORK);
	}
	pthread_mutex_lock(&philo->input->forks[philo->right_fork]);
	if (philo->input->dead_flag == 0)
	{
		philo->input->forks_status[philo->right_fork] = 1;
		print_message(philo, TAKEN_FORK);
	}
}

static void	regulated_usleep(unsigned long long time_to_sleep)
{
	unsigned long long	start;

	start = get_time() * 1000;
	while (get_time() * 1000 - start < time_to_sleep)
		usleep(100);
}
