#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	int	n;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_times_to_eat;
}				t_philo;

int	ft_atoi(const char *nptr);
int	validate_input(t_philo *options);
int	create_threads(t_philo *options);

#endif