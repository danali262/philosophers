#include "philo.h"

int	main(int argc, char **argv)
{
	t_input		input;
	t_philo	data;

	if (argc < 5)
	{
		printf("Please provide sufficient arguments\n");
		return (1);
	}
	input.n = ft_atoi(argv[1]);
	// printf("number of philosophers are %d\n", input.n);
	input.time_to_die = ft_atoi(argv[2]);
	// printf("time to die is %d ms\n", input.time_to_die);
	input.time_to_eat = ft_atoi(argv[3]);
	// printf("time to eat is %d ms\n", input.time_to_eat);
	input.time_to_sleep = ft_atoi(argv[4]);
	// printf("time to sleep is %d ms\n", input.time_to_sleep);
	if (argc == 6)
	{
		input.n_times_to_eat = ft_atoi(argv[5]);
		// printf("number of times a philo has to eat is %d\n", input.n_times_to_eat);
	}
	if (validate_input(&input, argc, argv) == -1)
		return (1);
	pthread_mutex_init(&data.fork, NULL);
	if (create_threads(&input, &data) == -1)
		return (1);
	pthread_mutex_destroy(&data.fork);
	return (0);
}
