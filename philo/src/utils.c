/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoiseik <amoiseik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:59:11 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/12 16:08:21 by amoiseik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_current_time(void)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return (tval.tv_sec * 1000 + tval.tv_usec / 1000);
}

static int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

static int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else 
		return (0);
}

int	ft_atoi(char *str)
{
	long	res;
	int		sign;

	sign = 1;
	res = 0;
	while (is_space(*str))
		str ++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str ++;
	}
	while (is_num(*str))
	{
		res = (*str - '0') + (res * 10);
		str ++;
	}
	res = res * sign;
	return ((int)res);
}

void	print_status(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->prog->end_mutex);
	if (philo->prog->end_flag != 1)
	{
		pthread_mutex_lock(&philo->prog->print_mutex);
		printf("%ld %d %s", \
			(get_current_time() - philo->prog->start_time), \
			philo->id, \
			message);
		pthread_mutex_unlock(&philo->prog->print_mutex);
	}
	pthread_mutex_unlock(&philo->prog->end_mutex);
}
