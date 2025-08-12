/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devriez <devriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:07:17 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/11 19:34:32 by devriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i ++;
	return (i);
}

void	free_all(t_prog *prog)
{
	if (prog->forks)
		free(prog->forks);
	if (prog->philos)
		free(prog->philos);
}

void	error_exit(char *message)
{
	write (2, message, ft_len(message));
	exit(EXIT_FAILURE);
}

void	error_free_exit(t_prog *prog, char *message)
{
	free_all(prog);
	error_exit(message);
}

void	destroy_mutexs(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philo)
	{
		pthread_mutex_destroy(&prog->forks[i]);
		i ++;
	}
	pthread_mutex_destroy(&prog->dead_or_full_mutex);
	pthread_mutex_destroy(&prog->print_mutex);
}
