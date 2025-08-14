/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoiseik <amoiseik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:11:33 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/14 19:45:23 by amoiseik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_philo_full(t_philo *philo)
{
	t_prog	*prog;
	int		res;

	res = 0;
	prog = philo->prog;
	if (prog->has_meal_limit)
	{
		pthread_mutex_lock(&philo->times_eated_mutex);
		if (philo->times_eated >= prog->meal_limit)
			res = 1;
		else
			res = 0;
		pthread_mutex_unlock(&philo->times_eated_mutex);
		return (res);
	}
	else
		return (0);
}

static int	is_philo_dead(t_philo *philo)
{
	int		time_no_eat;
	t_prog	*prog;

	prog = philo->prog;
	pthread_mutex_lock(&philo->last_time_eat_mutex);
	time_no_eat = get_current_time() - philo->last_time_eat;
	pthread_mutex_unlock(&philo->last_time_eat_mutex);
	if (time_no_eat > prog->time_to_die)
		return (1);
	else
		return (0);
}

static void	set_end_flag(t_philo *philo)
{
	t_prog	*prog;

	prog = philo->prog;
	pthread_mutex_lock(&prog->end_mutex);
	prog->end_flag = 1;
	pthread_mutex_unlock(&prog->end_mutex);
}

static void	print_last_status(t_philo *philo, int status)
{
	t_prog	*prog;

	prog = philo->prog;
	if (status == STATUS_EVERYBODY_FULL)
	{
		pthread_mutex_lock(&prog->print_mutex);
		printf("%ld %s", \
			(get_current_time() - prog->start_time), \
			STATUS_EVERYBODY_FULL_TEXT);
		pthread_mutex_unlock(&prog->print_mutex);
	}
	else if (status == STATUS_DEAD)
	{
		pthread_mutex_lock(&prog->print_mutex);
		printf("%ld %i %s", \
			(get_current_time() - prog->start_time), \
			philo->id, \
			STATUS_DEAD_TEXT);
		pthread_mutex_unlock(&prog->print_mutex);
	}
}

void	*observer_routine(void *param)
{
	int		i;
	int		full_count;
	t_philo	*philo;
	t_prog	*prog;

	prog = (t_prog *)param;
	while (1)
	{
		i = 0;
		full_count = 0;
		while (i < prog->num_of_philo)
		{
			philo = &prog->philos[i++];
			if (is_philo_full(philo))
				full_count ++;
			if (is_philo_dead(philo))
				return (set_end_flag(philo), \
						print_last_status(philo, STATUS_DEAD), NULL);
			if (full_count == prog->num_of_philo)
				return (set_end_flag(philo), \
						print_last_status(philo, STATUS_EVERYBODY_FULL), \
						NULL);
		}
		usleep(1000);
	}
}
