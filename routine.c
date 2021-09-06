#include "philo.h"

void	picks_forks(t_philo *philo)
{
	if (philo->index % 2 == 1)
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
	else
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
	philo->state = EATING;
}

static void	ft_sleep(unsigned long long time_to_sleep)
{
	unsigned long long	start;

	start = get_time() * 1000;
	while (get_time() * 1000 - start < time_to_sleep)
		usleep(100);
}

void	eats(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->dead_philo);
	philo->time_since_last_meal = get_time();
	print_message(philo, EATING);
	pthread_mutex_unlock(&philo->input->dead_philo);
	ft_sleep(philo->input->time_to_eat * 1000);
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
	ft_sleep(philo->input->time_to_sleep * 1000);
	philo->state = THINKING;
}

void	thinks(t_philo *philo)
{
	print_message(philo, THINKING);
}
