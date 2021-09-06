/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: danali <danali@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/06 15:27:09 by danali        #+#    #+#                 */
/*   Updated: 2021/09/06 16:20:20 by danali        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parser(int argc, char **argv, t_input *input)
{
	if (argc < 5 || argc > 6)
	{
		printf("Please provide a correct number of arguments\n");
		return (-1);
	}
	initialize_input(input);
	input->n = ft_atoi(argv[1]);
	input->time_to_die = ft_atoi(argv[2]);
	input->time_to_eat = ft_atoi(argv[3]);
	input->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input->n_times_to_eat = ft_atoi(argv[5]);
	return (0);
}

static int	error_messages(int option)
{
	if (option == 1)
		printf("Please provide a valid number of philosophers.\n");
	if (option == 2)
		printf("Please provide a valid time to die.\n");
	if (option == 3)
		printf("Please provide a valid time to eat.\n");
	if (option == 4)
		printf("Please provide a valid time to sleep.\n");
	if (option == 5)
		printf("Please provide a valid no of times a philosopher has to eat.\n");
	return (-1);
}

int	validate_input(t_input *input, int argc, char **argv)
{
	int	ret;

	ret = 0;
	if (input->n <= 0 || !is_numeric(argv[1]))
		ret = error_messages(1);
	if (!is_numeric(argv[2]))
		ret = error_messages(2);
	if (!is_numeric(argv[3]))
		ret = error_messages(3);
	if (!is_numeric(argv[4]))
		ret = error_messages(4);
	if (argc == 6)
	{
		if (!is_numeric(argv[5]))
			ret = error_messages(5);
	}
	return (ret);
}
