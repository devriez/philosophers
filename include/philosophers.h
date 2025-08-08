/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoiseik <amoiseik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:07:33 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/08 18:01:16 by amoiseik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>     // printf
# include <stdlib.h>    // malloc, free
# include <unistd.h>    // usleep()
# include <sys/time.h>  // gettimeofday()
# include <pthread.h>   // pthread functions

typedef struct s_program
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;

	int				is_dead;

	t_philosoph		*philosophs;

	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
}	t_program;

typedef struct s_philo
{
	int				id;
	long			last_time_eat;
	int				times_eated;

	t_program		program;

	pthread_t		thread;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philosoph;

#endif