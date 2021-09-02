#include "philo.h"

void	print_message(unsigned long long timestamp, t_philo *philo, int option)
{
	pthread_mutex_lock(&philo->input->print);
	philo->input->print_debug = 1;
	// if (option == TAKEN_FORK)
	// 	printf("%lld Philosopher %d has taken a fork.\n", timestamp, philo->index);
	if (option == EATING)
		printf("%lld Philosopher %d is eating.\n", timestamp, philo->index);
	if (option == SLEEPING)
		printf("%lld Philosopher %d is sleeping.\n", timestamp, philo->index);
	if (option == THINKING)
		printf("%lld Philosopher %d is thinking.\n", timestamp, philo->index);
	if (option == DIED)
		printf("%lld Philosopher %d died.\n", timestamp, philo->index);
	pthread_mutex_unlock(&philo->input->print);
	philo->input->print_debug = 0;
}

void	print_taken_fork(unsigned long long timestamp, t_philo *philo, int no_fork)
{
	pthread_mutex_unlock(&philo->input->forks[no_fork]);
	pthread_mutex_lock(&philo->input->print);
	printf("%lld Philosopher %d has taken a fork.\n", timestamp, philo->index);
	pthread_mutex_unlock(&philo->input->print);
	pthread_mutex_lock(&philo->input->forks[no_fork]);
}