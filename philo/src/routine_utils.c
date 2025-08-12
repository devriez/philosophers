/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoiseik <amoiseik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:33:47 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/12 19:06:23 by amoiseik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_end(t_prog *prog)
{
	int	res;

	pthread_mutex_lock(&prog->end_mutex);
	res = prog->end_flag;
	pthread_mutex_unlock(&prog->end_mutex);
	return (res);
}

void	set_last_time_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_time_eat_mutex);
	philo->last_time_eat = get_current_time();
	pthread_mutex_unlock(&philo->last_time_eat_mutex);
}

void	sleeping(t_philo	*philo)
{
	print_status(philo, "is sleeping\n");
	usleep(philo->prog->time_to_sleep * 1000);
}

void	thinking(t_philo	*philo)
{
	print_status(philo, "is thinking\n");
	usleep(1000); 
}
