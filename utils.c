/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 22:31:15 by jtardieu          #+#    #+#             */
/*   Updated: 2026/06/26 16:30:05 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


#include <time.h>

long long get_current_time_ms(void)
{
	return (time(NULL) * 1000);
}

void	cleanup_simulation(t_sim *sim)
{
	int	i;
	int	nb_dongles;

	if (sim->coders)
	{
		free(sim->coders);
		sim->coders = NULL;
	}

	if (sim->dongles)
	{
		nb_dongles = sim->params.number_of_coders;
		if (nb_dongles == 1)
			nb_dongles = 1;
		else
			nb_dongles = sim->params.number_of_coders;

		i = 0;
		while (i < nb_dongles)
		{
			pthread_mutex_destroy(&sim->dongles[i].mutex);
			i++;
		}
		free(sim->dongles);
		sim->dongles = NULL;
	}

	pthread_mutex_destroy(&sim->log_mutex);
}