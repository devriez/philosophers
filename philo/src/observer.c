/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devriez <devriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:11:33 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/11 15:59:26 by amoiseik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_full(t_philo *philo)
{
	t_prog	*prog;
	int		res;

	res = 0;
	prog = philo->prog;
	pthread_mutex_lock(&philo->times_eated_mutex);
	if (prog->num_to_eat_each != -1 && philo->times_eated >= prog->num_to_eat_each)
		res = 1;
	pthread_mutex_unlock(&philo->times_eated_mutex);
	return (res);
}

int	is_dead(t_philo *philo)
{
	int		time_no_eat;
	int		res;
	t_prog	*prog;

	res = 0;
	prog = philo->prog;
	pthread_mutex_lock(&philo->last_time_eat_mutex);
	time_no_eat = get_current_time() - philo->last_time_eat;
	pthread_mutex_unlock(&philo->last_time_eat_mutex);
	if (time_no_eat > prog->time_to_die)
		res = 1;
	return (res);
}

void	set_end_flag(t_philo *philo)
{
	t_prog	*prog;

	prog = philo->prog;
	pthread_mutex_lock(&prog->dead_or_full_mutex);
	prog->is_dead_or_full = 1;
	pthread_mutex_unlock(&prog->dead_or_full_mutex);
}

void	print_last_status(t_philo *philo, char *status)
{
	t_prog *prog;

	prog = philo->prog;
	pthread_mutex_lock(&prog->print_mutex);
	printf("%ld %d %s", \
		(get_current_time() - prog->start_time), \
		philo->id, \
		status);
	pthread_mutex_unlock(&prog->print_mutex);
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
			if (is_full(philo))
				full_count ++;
			if (is_dead(philo))
				return (set_end_flag(philo), \
						print_last_status(philo, "died\n"), NULL);
			if (full_count == prog->num_of_philo)
				return (set_end_flag(philo), \
						print_last_status(philo, "Everybody ate enough times"), \
						NULL);
		}
		usleep(100);
	}
}
