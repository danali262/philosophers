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
