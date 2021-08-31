#include "philo.h"

unsigned long long	ft_atoi(const char *str)
{
	int 				i;
	unsigned long long	n;

	i = 0;
	n = 0;
	while (str[i] != '\0')
	{
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	return (n);
}

int	is_numeric(char *c)
{
	int i;

	i = 0;
	while (c[i] != '\0')
	{
		if (c[i] < 48 || c[i] > 57)
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

static void	ft_bzero(void *s, size_t n)
{
	unsigned char *ptr;

	ptr = NULL;
	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = '\0';
		ptr++;
		n--;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
