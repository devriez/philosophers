/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoiseik <amoiseik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:14:11 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/12 15:01:02 by amoiseik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork\n");
	}
}

static void	put_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

static int	check_is_dead_or_full(t_philo *philo)
{
	int		res;
	t_prog	*prog;

	prog = philo->prog;
	res = 0;
	pthread_mutex_lock(&prog->dead_or_full_mutex);
	if (prog->is_dead_or_full)
		res = 1;
	pthread_mutex_unlock(&prog->dead_or_full_mutex);
	return (res);
}

static void	eating(t_philo	*philo)
{
	pthread_mutex_lock(&philo->last_time_eat_mutex);
	philo->last_time_eat = get_current_time();
	pthread_mutex_unlock(&philo->last_time_eat_mutex);
	print_status(philo, "is eating\n");
	usleep(philo->prog->time_to_eat * 1000);
	if (philo->times_eated != -1)
	{
		pthread_mutex_lock(&philo->times_eated_mutex);
		philo->times_eated ++;
		pthread_mutex_unlock(&philo->times_eated_mutex);
	}
}

void	*routine(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	usleep(WAIT_TIME);
	while (1)
	{
		take_forks(philo);
		if (check_is_dead_or_full(philo))
		{
			put_forks(philo);
			return (NULL);
		}
		else
		{
			eating(philo);
			put_forks(philo);
		}
		print_status(philo, "is sleeping\n");
		usleep(philo->prog->time_to_sleep * 1000);
		print_status(philo, "is thinking\n");
	}
}
