/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: danali <danali@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/06 16:05:00 by danali        #+#    #+#                 */
/*   Updated: 2021/09/06 16:10:53 by danali        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_threads(pthread_t *philo_group, t_input *input)
{
	int	i;

	i = 0;
	while (i < input->n)
	{
		if (pthread_join(philo_group[i], NULL) != 0)
		{
			free(philo_group);
			printf("Failed to join the threads\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	create_threads(t_input *input, t_philo *philo)
{
	pthread_t	*philo_group;
	int			i;

	philo_group = ft_calloc(input->n, sizeof(pthread_t));
	if (!philo_group)
		return (-1);
	i = 0;
	while (i < input->n)
	{
		philo[i].index = i + 1;
		if (pthread_create(&philo_group[i], NULL, routine, &philo[i]) != 0)
		{
			free(philo_group);
			printf("Failed to create the threads\n");
			return (-1);
		}
		i++;
	}
	if (join_threads(philo_group, input) == -1)
		return (-1);
	free(philo_group);
	return (0);
}
