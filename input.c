#include "philo.h"

int	validate_input(t_input *input, int argc, char **argv)
{
	if (input->n <= 0 || !is_numeric(argv[1]))
	{
		printf("Please provide a valid number of philosophers.\n");
		return (-1);
	}
	if (input->time_to_die <= 0 || !is_numeric(argv[2]))
	{
		printf("Please provide a valid time to die.\n");
		return (-1);
	}
	if (input->time_to_eat <= 0 || !is_numeric(argv[3]))
	{
		printf("Please provide a valid time to eat.\n");
		return (-1);
	}
	if (input->time_to_sleep <= 0 || !is_numeric(argv[4]))
	{
		printf("Please provide a valid time to sleep.\n");
		return (-1);
	}
	if (argc == 6)
	{
		if (input->n_times_to_eat <= 0 || !is_numeric(argv[5]))
		{
			printf("Please provide a valid number of time a philo has to eat.\n");
			return (-1);
		}
	}
	return (0);
}