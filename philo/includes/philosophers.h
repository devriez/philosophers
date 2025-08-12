/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoiseik <amoiseik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:07:33 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/12 14:59:38 by amoiseik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define WAIT_TIME			   		100

# define STATUS_DEAD		   		0
# define STATUS_EVERYBODY_FULL 		1
# define STATUS_DEAD_TEXT			"died\n"
# define STATUS_EVERYBODY_FULL_TEXT "All philosophers ate enough times\n"

# include <stdio.h>     // printf
# include <stdlib.h>    // malloc, free
# include <unistd.h>    // usleep()
# include <sys/time.h>  // gettimeofday()
# include <pthread.h>   // pthread functions

typedef struct s_prog	t_prog;

typedef struct s_philo
{
	int				id;
	long			last_time_eat;
	int				times_eated;

	t_prog			*prog;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_time_eat_mutex;
	pthread_mutex_t	times_eated_mutex;

	pthread_t		thread;
}	t_philo;

typedef struct s_prog
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat_each;

	long			start_time;
	int				is_dead_or_full;

	pthread_t		observe;

	t_philo			*philos;

	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_or_full_mutex;
	pthread_mutex_t	print_mutex;
}	t_prog;

//utils
long	get_current_time(void);
int		ft_atoi(char *str);
void	print_status(t_philo *philo, char *message);
//observer
void	*observer_routine(void *param);
//routine
void	*routine(void	*arg);
//free_and_error
void	free_all(t_prog *prog);
void	error_exit(char *message);
void	error_free_exit(t_prog *prog, char *message);
void	destroy_mutexs(t_prog *prog);
//init
void	init_struct(t_prog *prog, int argc, char **argv);

#endif