#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo		options;

	if (argc < 5)
	{
		printf("Please provide sufficient arguments\n");
		return (1);
	}
	options.n = ft_atoi(argv[1]);
	printf("number of philosophers are %d\n", options.n);
	options.time_to_die = ft_atoi(argv[2]);
	printf("time to die is %d ms\n", options.time_to_die);
	options.time_to_eat = ft_atoi(argv[3]);
	printf("time to eat is %d ms\n", options.time_to_eat);
	options.time_to_sleep = ft_atoi(argv[4]);
	printf("time to sleep is %d ms\n", options.time_to_sleep);
	if (argc == 6)
	{
		options.n_times_to_eat = ft_atoi(argv[5]);
		printf("number of times a philo has to eat is %d\n", options.n_times_to_eat);
	}
	validate_input(&options);
	if (create_threads(&options) == -1)
		return (1);
	return (0);
}