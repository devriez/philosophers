/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoiseik <amoiseik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:07:17 by amoiseik          #+#    #+#             */
/*   Updated: 2025/08/09 15:11:50 by amoiseik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	fr_len(char **str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i ++;
	return (i);
}

int	free_all(t_prog *prog)
{
	if (prog->forks)
		free(prog->forks);
		//add free froks
	if (prog->philosophs)
		free(prog->philosophs);
}

void	my_error(char *message, t_prog *prog)
{
	write (2, message, ft_len(message));
	free_all(prog);
	exit(EXIT_FAILURE);
}
