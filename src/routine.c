/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoiseik <amoiseik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:14:11 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/10 16:05:26 by amoiseik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		while (pthread_mutex_lock(philo->left_fork) != 0)
			usleep(200);
		print_status(philo, "has taken a fork");
		while (pthread_mutex_lock(philo->right_fork) != 0)
			usleep(200);
		print_status(philo, "has taken a fork");
	}
	else
	{
		while (pthread_mutex_lock(philo->right_fork) != 0)
			usleep(200);
		print_status(philo, "has taken a fork");
		while (pthread_mutex_lock(philo->left_fork) != 0)
			usleep(200);
		print_status(philo, "has taken a fork");
	}
}

void	put_forks(t_philo *philo)
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


int	check_is_dead_or_full(t_philo *philo)
{
	int	end;

	end = 0;
	pthread_mutex_lock(&philo->prog->dead_or_full_mutex);
	if (get_current_time() - philo->last_time_eat > philo->prog->time_to_die)
	{
		philo->prog->is_dead_or_full = 1;
		end = 1;
	}
	else if (philo->prog->is_dead_or_full)
		end = 1;
	else if (philo->times_eated >= philo->prog->num_to_eat)
	{
		philo->prog->is_dead_or_full = 1;
		end = 1;
	}
	pthread_mutex_unlock(&philo->prog->is_dead_or_full);
	return (end);
}

void	eating(t_philo	*philo)
{
	philo->last_time_eat = get_current_time();
	print_status(philo, "is eating");
	usleep(philo->prog->time_to_eat * 1000);
	if (philo->times_eated != -1)
		philo->times_eated ++;
}

void	*routine(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	usleep(SLEEP_TIME);
	while (1)
	{
		take_forks(philo);
		if (check_is_dead_or_full(philo))
		{
			put_forks(philo);
			break ;
		}
		else
		{
			eating(philo);
			put_forks(philo);
		}
		print_status(philo, "is sleeping");
		usleep(philo->prog->time_to_sleep * 1000);
		print_status(philo, "is thinking");
	}
}
