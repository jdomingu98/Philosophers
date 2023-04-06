#include "philosophers.h"

long	ft_atoi_long(char *str)
{
	long	nbr;
	int		i;
	int		sign;

	nbr = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		i++;
		sign = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
}

static int	is_positive_int_in_range(char *str, int av_idx)
{
	long	nbr;
	int		nbr_condition;

	nbr = ft_atoi_long(str);
	nbr_condition = nbr >= 0;
	if (av_idx == 1)
		nbr_condition = nbr > 0;
	return (nbr_condition && nbr <= INT_MAX);
}

int	valid_args(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!is_positive_int_in_range(av[i], i))
			return (0);
	}
	return (1);
}