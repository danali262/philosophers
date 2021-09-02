#include "philo.h"

void	picks_forks(t_philo *philo)
{
	unsigned long long	timestamp;

	pthread_mutex_lock(&philo->input->forks[philo->left_fork]);
	philo->input->forks_debug[philo->left_fork] = 1;
	timestamp = get_time() - philo->start_time;
	print_message(timestamp, philo, TAKEN_FORK);
	pthread_mutex_lock(&philo->input->forks[philo->right_fork]);
	philo->input->forks_debug[philo->right_fork] = 1;
	timestamp = get_time() - philo->start_time;
	print_message(timestamp, philo, TAKEN_FORK);
	if (philo->input->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->input->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->input->forks[philo->left_fork]);
		return ;
	}
	philo->state = EATS;
}

void	eats(t_philo *philo)
{
	unsigned long long timestamp;

	if (philo->input->dead_flag == 1)
		return ;
	timestamp = get_time() - philo->start_time;
	print_message(timestamp, philo, EATING);
	philo->time_since_last_meal = get_time();
	philo->times_eaten++;
	usleep(1000 * philo->input->time_to_eat);
	philo->state = DONE_EATING;
}

void	drops_forks(t_philo *philo)
{
	if (philo->input->dead_flag == 1)
		return ;
	pthread_mutex_unlock(&philo->input->forks[philo->left_fork]);
	philo->input->forks_debug[philo->left_fork] = 0;
	pthread_mutex_unlock(&philo->input->forks[philo->right_fork]);
	philo->input->forks_debug[philo->right_fork] = 0;
	philo->state = SLEEPS;
}

void	sleeps(t_philo *philo)
{
	unsigned long long timestamp;

	if (philo->input->dead_flag == 1)
		return ;
	timestamp = get_time() - philo->start_time;
	print_message(timestamp, philo, SLEEPING);
	usleep(1000 * philo->input->time_to_sleep);
	philo->state = THINKS;
}

void	thinks(t_philo *philo)
{
	unsigned long long timestamp;

	if (philo->input->dead_flag == 1)
		return ;
	timestamp = get_time() - philo->start_time;
	print_message(timestamp, philo, THINKING);
	philo->state = WANTS_TO_EAT;
}
