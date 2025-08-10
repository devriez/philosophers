/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoiseik <amoiseik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:11:33 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/10 16:24:44 by amoiseik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	simulation(t_prog	*prog)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philo)
	{
		pthread_create(prog->philos[i].thread, NULL, routine, &prog->philos[i]);
		i ++;
	}
}

void	wait_end_of_threads(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philo)
	{
		pthread_join(prog->philos[i].thread, NULL);
	}
}

int	main(int argc, char **argv)
{
	t_prog	prog;

	if (argc < 5 && argc > 6)
	{
		init_struct(&prog, argv);
		simulation(&prog);
		wait_end_of_threads(&prog);
		free_recources(&prog);//write
		return (0);
	}
	else
	{
		my_error_exit(&prog, "invalid number of arguments");
	}
}
