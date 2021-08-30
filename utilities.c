#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int res;
	int sign;

	res = 0;
	sign = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\f' || *nptr == '\r' ||
	*nptr == '\n' || *nptr == '\v')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - 48);
		nptr++;
	}
	return (res * sign);
}

int	is_numeric(char *c)
{
	int i;

	i = 0;
	while (c[i] != '\0')
	{
		if (c[i] < 48 && c[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

unsigned long long	get_time(void)
{
	struct timeval		stop;
	unsigned long long	time;

	gettimeofday(&stop, NULL);
	time = (stop.tv_sec * 1000) + (stop.tv_usec /1000);
	return (time);
}
