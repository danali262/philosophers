#include "philo.h"

void	picks_forks(t_philo *philo)
{
	unsigned long long	timestamp;

	pthread_mutex_lock(&philo->input->forks[philo->left_fork]);
	timestamp = get_time() - philo->start_time;
	print_message(timestamp, philo, TAKEN_FORK);
	pthread_mutex_lock(&philo->input->forks[philo->right_fork]);
	timestamp = get_time() - philo->start_time;
	print_message(timestamp, philo, TAKEN_FORK);
	philo->state = EATS;
}

void	eats(t_philo *philo)
{
	unsigned long long timestamp;

	timestamp = get_time() - philo->start_time;
	print_message(timestamp, philo, EATING);
	philo->time_since_last_meal = get_time();
	philo->times_eaten++;
	usleep(1000 * philo->input->time_to_eat);
	philo->state = DONE_EATING;
}

void	drops_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->input->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->input->forks[philo->right_fork]);
	philo->state = SLEEPS;
}

void	sleeps(t_philo *philo)
{
	unsigned long long timestamp;

	timestamp = get_time() - philo->start_time;
	print_message(timestamp, philo, SLEEPING);
	usleep(1000 * philo->input->time_to_sleep);
	philo->state = THINKS;
}

void	thinks(t_philo *philo)
{
	unsigned long long timestamp;

	timestamp = get_time() - philo->start_time;
	print_message(timestamp, philo, THINKING);
}