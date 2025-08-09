/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoiseik <amoiseik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:07:33 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/09 15:57:41 by amoiseik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define SLEEP_TIME	200

# include <stdio.h>     // printf
# include <stdlib.h>    // malloc, free
# include <unistd.h>    // usleep()
# include <sys/time.h>  // gettimeofday()
# include <pthread.h>   // pthread functions

typedef struct s_prog
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;

	long			start_time;
	int				is_dead;

	t_philo			*philosophs;

	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
}	t_prog;

typedef struct s_philo
{
	int				id;
	long			last_time_eat;
	int				times_eated;

	t_prog			*prog;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	pthread_t		thread;
}	t_philo;

long	get_current_time(void);
int		ft_atoi(char *str);
void	print_status(t_philo *philo, char *message);

#endif