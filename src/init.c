/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoiseik <amoiseik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:12:13 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/09 15:22:08 by amoiseik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_prog *prog, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].last_time_eat = prog->start_time;
		philo[i].times_eated = 0;
		philo->prog = prog;
		philo[i].left_fork = &prog->forks[i];
		philo[i].right_fork = &prog->forks[(i + 1) % prog->num_of_philo];
		pthread_create(philo[i].thread, NULL, routine, &philo[i]);
		i ++;
	}
}

void	init_prog(t_prog *prog, char **argv)
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
	prog->is_dead = 0;
	prog->philosophs = malloc(sizeof(t_philo) * (prog->num_of_philo));
	prog->forks = malloc(sizeof(pthread_mutex_t) * (prog->num_of_philo));
	if (!prog->philosophs || !prog->forks)
		my_error("Errror memory allocation for philosophs or forks", prog);
	i = 0;
	while (i < prog->num_of_philo)
	{
		pthread_mutex_init(&(prog->forks[i]), NULL);
		i ++;
	}
	pthread_mutex_init(&(prog->death_mutex), NULL);
	pthread_mutex_init(&(prog->print_mutex), NULL);
	init_philo(prog, prog->philosophs);
}
