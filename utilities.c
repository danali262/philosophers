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
