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
	int								dead_flag;
	pthread_mutex_t 				*forks;
	pthread_mutex_t					print;
	pthread_mutex_t					dead_philo;
}				t_input;

typedef	enum	e_states
{
	WANTS_TO_EAT,
	EATS,
	DONE_EATING,
	SLEEPS,
	THINKS
}				t_states;

typedef struct s_philo
{
	t_input				*input;
	int					index;
	int					state;
	int					left_fork;
	int					right_fork;
	int					times_eaten;
	unsigned long long	start_time;
	unsigned long long	time_since_last_meal;
}				t_philo;

typedef enum	e_options
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}				t_options;

unsigned long long	ft_atoi(const char *nptr);
int					is_numeric(char *c);
void				*ft_calloc(size_t nmemb, size_t size);
unsigned long long	get_time(void);

void				initialize_input(t_input *input);
int					validate_input(t_input *input, int argc, char **argv);
int					initialize_philosophers(t_input *input, t_philo *philo);
int					initialize_mutex(t_philo *philo);
void				destroy_mutex(t_philo *philo);

int					create_threads(t_input *input, t_philo *philo);
void				picks_forks(t_philo *philo);
void				drops_forks(t_philo *philo);
void				eats(t_philo *philo);
void				sleeps(t_philo *philo);
void				thinks(t_philo *philo);

void				print_message(unsigned long long timestamp, t_philo *philo, int option);

#endif