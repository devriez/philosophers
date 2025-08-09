/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoiseik <amoiseik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:14:11 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/09 15:57:41 by amoiseik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routin(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	usleep(100);
	print_status(philo, "is thinking");
	if (pthread_mutex_lock(&philo->prog->death_mutex) != 0)
		usleep(SLEEP_TIME);
	if (philo->prog->is_dead != 1)
	{
		if ((get_current_time() - philo->last_time_eat) < philo->prog->time_to_die)
	}
}
