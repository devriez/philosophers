/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoiseik <amoiseik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:12:13 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/14 19:46:31 by amoiseik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philos(t_prog *prog, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].times_eated = 0;
		philo[i].last_time_eat = prog->start_time;
		philo[i].prog = prog;
		philo[i].left_fork = &prog->forks[i];
		philo[i].right_fork = &prog->forks[(i + 1) % prog->num_of_philo];
		pthread_mutex_init(&(philo[i].last_time_eat_mutex), NULL);
		pthread_mutex_init(&(philo[i].times_eated_mutex), NULL);
		i ++;
	}
}

static void	parse_and_validate_args(t_prog *prog, int argc, char **argv)
{
	prog->num_of_philo = ft_atoi(argv[1]);
	prog->time_to_die = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		prog->has_meal_limit = 1;
		prog->meal_limit = ft_atoi(argv[5]);
	}
	else
		prog->has_meal_limit = 0;
	if (prog->num_of_philo < 1)
		error_exit("Invalid number of philos. Must be a positive integer.\n");
	if (prog->time_to_die < 1)
		error_exit("Invalid time to die. Must be a positive integer.\n");
	if (prog->time_to_eat < 1)
		error_exit("Invalid time to eat. Must be a positive integer.\n");
	if (prog->time_to_sleep < 1)
		error_exit("Invalid time to sleep. Must be a positive integer.\n");
	if ((prog->has_meal_limit == 1) && (prog->meal_limit < 1))
		error_exit("Invalid meal limit. Must be a positive integer.\n");
}

void	init_struct(t_prog *prog, int argc, char **argv)
{
	int	i;

	parse_and_validate_args(prog, argc, argv);
	prog->start_time = get_current_time();
	prog->end_flag = 0;
	prog->philos = malloc(sizeof(t_philo) * (prog->num_of_philo));
	prog->forks = malloc(sizeof(pthread_mutex_t) * (prog->num_of_philo));
	if (!prog->philos || !prog->forks)
		error_free_exit(prog, "Error memory alloc for philosophs or forks\n");
	i = 0;
	while (i < prog->num_of_philo)
	{
		pthread_mutex_init(&(prog->forks[i]), NULL);
		i ++;
	}
	pthread_mutex_init(&(prog->end_mutex), NULL);
	pthread_mutex_init(&(prog->print_mutex), NULL);
	init_philos(prog, prog->philos);
}
