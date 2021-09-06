#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_input	input;

	if (argc < 5)
	{
		printf("Please provide sufficient arguments\n");
		return (-1);
	}
	initialize_input(&input);
	input.n = ft_atoi(argv[1]);
	input.time_to_die = ft_atoi(argv[2]);
	input.time_to_eat = ft_atoi(argv[3]);
	input.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input.n_times_to_eat = ft_atoi(argv[5]);
	if (validate_input(&input, argc, argv) == -1)
		return (-1);
	if (initialize_mutex(&input) == -1)
		return (-1);
	philo = ft_calloc(input.n, sizeof(t_philo));
	if (!philo)
	{
		free(input.forks);
		free(input.forks_status);
		return (-1);
	}
	if (initialize_philosophers(&input, philo) == -1)
	{
		free(input.forks);
		free(input.forks_status);
		free(philo);
		return (-1);
	}
	if (create_threads(&input, philo) == -1)
	{
		free(input.forks);
		free(input.forks_status);
		free(philo);
		return (-1);
	}
	destroy_mutex(&input);
	free(philo);
	free(input.forks);
	free(input.forks_status);
	return (0);
}
