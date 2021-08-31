#include "philo.h"

void	picks_forks(t_philo *philo)
{
	unsigned long long	timestamp;

	timestamp = 0;
	// philo->timestamp = get_time();
	pthread_mutex_lock(&philo->input->forks[philo->left_fork]);
	// timestamp = get_time() - philo->timestamp;
	// philo->timestamp = get_time();
	printf("%llu Philosopher %d has taken a fork.\n", timestamp, philo->index);
	// usleep(10);
	// timestamp = get_time() - philo->timestamp;
	// philo->timestamp = get_time();
	pthread_mutex_lock(&philo->input->forks[philo->right_fork]);
	printf("%llu Philosopher %d has taken a fork.\n", timestamp, philo->index);
}

void	eats(t_philo *philo)
{
	printf("Philosopher %d is eating.\n", philo->index);
}

void	drops_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->input->forks[philo->left_fork]);
	printf("Philosopher %d drops the fork.\n", philo->index);
	pthread_mutex_unlock(&philo->input->forks[philo->right_fork]);
	printf("Philosopher %d drops the fork.\n", philo->index);
}

void	sleeps(t_philo *philo)
{
	printf("Philosopher %d is sleeping.\n", philo->index);
}

void	thinks(t_philo *philo)
{
	printf("Philosopher %d is thinking.\n", philo->index);
}