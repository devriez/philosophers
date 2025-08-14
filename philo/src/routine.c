/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoiseik <amoiseik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:14:11 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/14 19:43:24 by amoiseik         ###   ########.fr       */
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
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	eating(t_philo	*philo)
{
	set_last_time_eat(philo);
	print_status(philo, "is eating\n");
	usleep(philo->prog->time_to_eat * 1000);
	pthread_mutex_lock(&philo->times_eated_mutex);
	philo->times_eated ++;
	pthread_mutex_unlock(&philo->times_eated_mutex);
}

void	routine_alone(t_philo	*philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork\n");
	usleep(philo->prog->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_last_time_eat(philo);
	if (philo->prog->num_of_philo == 1)
		return (routine_alone(philo), NULL);
	while (1)
	{
		take_forks(philo);
		if (is_end(philo->prog))
		{
			put_forks(philo);
			return (NULL);
		}
		else
		{
			eating(philo);
			put_forks(philo);
		}
		sleeping(philo);
		thinking(philo);
	}
}
