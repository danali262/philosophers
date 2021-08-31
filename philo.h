#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_input
{
	int								n;
	unsigned long long				time_to_die;
	unsigned long long				time_to_eat;
	unsigned long long				time_to_sleep;
	int								n_times_to_eat;
	pthread_mutex_t *forks;
}				t_input;

typedef	enum	e_states
{
	PICKED_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}				t_states;

typedef struct s_philo
{
	t_input				*input;
	int					index;
	int					state;
	int					left_fork;
	int					right_fork;
	int					dead;
	int					times_eaten;
	unsigned long long	time_since_last_meal;
	unsigned long long	timestamp;
}				t_philo;

unsigned long long	ft_atoi(const char *nptr);
int					is_numeric(char *c);
void				*ft_calloc(size_t nmemb, size_t size);
unsigned long long	get_time(void);
void				initialize_input(t_input *input);
int					validate_input(t_input *input, int argc, char **argv);
int					initialize_philosophers(t_input *input, t_philo *philo);
int					initialize_mutex(t_philo *philo);
int					create_threads(t_input *input, t_philo *philosophers);
void				destroy_mutex(t_philo *philo);
void				picks_forks(t_philo *philosophers);
void				drops_forks(t_philo *philosophers);
void				eats(t_philo *philosophers);
void				sleeps(t_philo *philosophers);
void				thinks(t_philo *philosophers);

#endif