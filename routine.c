#include "philo.h"

void	picks_forks(t_philo *philo)
{
	unsigned long long	timestamp;

	pthread_mutex_lock(&philo->input->forks[philo->left_fork]);
	philo->input->forks_debug[philo->left_fork] = 1;
	timestamp = get_time() - philo->start_time;
	if (philo->input->dead_flag == 0)
		print_taken_fork(timestamp, philo, philo->left_fork);
	pthread_mutex_lock(&philo->input->forks[philo->right_fork]);
	philo->input->forks_debug[philo->right_fork] = 1;
	timestamp = get_time() - philo->start_time;
	if (philo->input->dead_flag == 0)
		print_taken_fork(timestamp, philo, philo->right_fork);
	philo->state = EATS;
}

void	eats(t_philo *philo)
{
	unsigned long long timestamp;

	pthread_mutex_lock(&philo->input->dead_philo);
	timestamp = get_time() - philo->start_time;
	print_message(timestamp, philo, EATING);
	philo->time_since_last_meal = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->input->dead_philo);
	usleep(1000 * philo->input->time_to_eat);
	pthread_mutex_unlock(&philo->input->forks[philo->left_fork]);
	philo->input->forks_debug[philo->left_fork] = 0;
	pthread_mutex_unlock(&philo->input->forks[philo->right_fork]);
	philo->input->forks_debug[philo->left_fork] = 0;
	philo->state = DONE_EATING;
}

static void	ft_sleep(unsigned long long time_to_sleep)
{
	unsigned long long	start;

	start = get_time();
	while (get_time() - start < time_to_sleep)
		usleep(100);
}

void	sleeps(t_philo *philo)
{
	unsigned long long timestamp;

	timestamp = get_time() - philo->start_time;
	print_message(timestamp, philo, SLEEPING);
	ft_sleep(philo->input->time_to_sleep *1000);
	// usleep(1000 * philo->input->time_to_sleep);
	philo->state = THINKS;
}

void	thinks(t_philo *philo)
{
	unsigned long long timestamp;

	timestamp = get_time() - philo->start_time;
	print_message(timestamp, philo, THINKING);
	philo->state = WANTS_TO_EAT;
}
