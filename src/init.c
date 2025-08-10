/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoiseik <amoiseik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:12:13 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/10 16:24:10 by amoiseik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philos(t_prog *prog, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].last_time_eat = prog->start_time;
		if (philo->prog->num_to_eat != -1)
			philo[i].times_eated = 0;
		else
			philo[i].times_eated = -1;
		philo->prog = prog;
		philo[i].left_fork = &prog->forks[i];
		philo[i].right_fork = &prog->forks[(i + 1) % prog->num_of_philo];
		i ++;
	}
}

void	init_struct(t_prog *prog, char **argv)
{
	int	i;

	prog->num_of_philo = argv[1];
	prog->time_to_die = argv[2];
	prog->time_to_eat = argv[3];
	prog->time_to_sleep = argv[4];
	if (argv[5])
		prog->num_to_eat = argv[5];
	else
		prog->num_to_eat = -1;
	prog->start_time = get_current_time();
	prog->is_dead_or_full = 0;
	prog->philos = malloc(sizeof(t_philo) * (prog->num_of_philo));
	prog->forks = malloc(sizeof(pthread_mutex_t) * (prog->num_of_philo));
	if (!prog->philos || !prog->forks)
		my_error_exit("Error memory allocation for philosophs or forks", prog);
	i = 0;
	while (i < prog->num_of_philo)
	{
		pthread_mutex_init(&(prog->forks[i]), NULL);
		i ++;
	}
	pthread_mutex_init(&(prog->dead_or_full_mutex), NULL);
	pthread_mutex_init(&(prog->print_mutex), NULL);
	init_philos(prog, prog->philos);
}

