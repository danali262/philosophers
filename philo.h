#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_input
{
	int	n;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_times_to_eat;
}				t_input;

typedef struct s_philo
{
	int	index;
	pthread_mutex_t fork;
}				t_philo;


int	ft_atoi(const char *nptr);
int	is_numeric(char *c);
int	validate_input(t_input *input, int argc, char **argv);
int	create_threads(t_input *input, t_philo *data);

#endif