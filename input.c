#include "philo.h"

int	validate_input(t_philo *options)
{
	if (options->n < 0)
	{
		printf("Please provide a valid number of philosophers.\n");
		return (-2);
	}

}