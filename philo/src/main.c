/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoiseik <amoiseik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:11:33 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/12 18:28:37 by amoiseik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	simulation(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philo)
	{
		pthread_create(&prog->philos[i].thread, NULL, \
						routine, \
						&prog->philos[i]);
		i ++;
	}
	pthread_create(&prog->observe, NULL, observer_routine, prog);
}

static void	wait_end_of_threads(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philo)
	{
		pthread_join(prog->philos[i].thread, NULL);
		i ++;
	}
	pthread_join(prog->observe, NULL);
}

int	main(int argc, char **argv)
{
	t_prog	prog;

	if (argc == 5 || argc == 6)
	{
		init_struct(&prog, argc, argv);
		simulation(&prog);
		wait_end_of_threads(&prog);
		destroy_mutexs(&prog);
		free_all(&prog);
		return (0);
	}
	else
	{
		error_exit("invalid number of arguments\n");
	}
}
