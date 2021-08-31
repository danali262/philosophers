#include "philo.h"

void	picks_forks(t_philo *philo)
{
	unsigned long long	timestamp;

	pthread_mutex_lock(&philo->input->forks[philo->left_fork]);
	timestamp = get_time() - philo->start_time;
	printf("%lld Philosopher %d has taken fork %d.\n", timestamp, philo->index, philo->left_fork);
	pthread_mutex_lock(&philo->input->forks[philo->right_fork]);
	timestamp = get_time() - philo->start_time;
	printf("%lld Philosopher %d has taken fork %d.\n", timestamp, philo->index, philo->right_fork);
	philo->state = EATING;
}

void	eats(t_philo *philo)
{
	unsigned long long timestamp;

	timestamp = get_time() - philo->start_time;
	printf("%lld Philosopher %d is eating.\n", timestamp, philo->index);
	philo->time_since_last_meal = get_time();
	philo->times_eaten++;
	usleep(1000 * philo->input->time_to_eat);
	philo->state = DONE_EATING;
}

void	drops_forks(t_philo *philo)
{
	unsigned long long	timestamp;

	pthread_mutex_unlock(&philo->input->forks[philo->left_fork]);
	timestamp = get_time() - philo->start_time;
	printf("%lld Philosopher %d drops fork %d.\n", timestamp, philo->index, philo->left_fork);
	pthread_mutex_unlock(&philo->input->forks[philo->right_fork]);
	timestamp = get_time() - philo->start_time;
	printf("%lld Philosopher %d drops fork %d.\n", timestamp, philo->index, philo->right_fork);
	philo->state = SLEEPING;
}

void	sleeps(t_philo *philo)
{
	unsigned long long timestamp;

	timestamp = get_time() - philo->start_time;
	printf("%lld Philosopher %d is sleeping.\n", timestamp, philo->index);
	usleep(1000 * philo->input->time_to_sleep);
	philo->state = THINKING;
}

void	thinks(t_philo *philo)
{
	unsigned long long timestamp;

	timestamp = get_time() - philo->start_time;
	printf("%lld Philosopher %d is thinking.\n", timestamp, philo->index);
}