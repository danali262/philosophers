/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: danali <danali@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/06 15:35:32 by danali        #+#    #+#                 */
/*   Updated: 2021/09/06 15:42:45 by danali        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_allocated(t_input *input, t_philo *philo)
{
	free(input->forks);
	free(input->forks_status);
	free(philo);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_input	input;

	if (parser(argc, argv, &input) == -1)
		return (-1);
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
	initialize_philosophers(&input, philo);
	if (create_threads(&input, philo) == -1)
	{
		free_allocated(&input, philo);
		return (-1);
	}
	destroy_mutex(&input);
	free_allocated(&input, philo);
	return (0);
}
