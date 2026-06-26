/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 22:31:15 by jtardieu          #+#    #+#             */
/*   Updated: 2026/06/26 17:38:19 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


#include <time.h>

long long get_current_time_ms(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);

	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
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

void	log_message(t_sim *sim, int coder_id, const char *action)
{
	long long	elapsed_time;


	elapsed_time = get_current_time_ms() - sim->start_time;
	pthread_mutex_lock(&sim->log_mutex);
	printf("%lld %d %s\n", elapsed_time, coder_id, action);
	pthread_mutex_unlock(&sim->log_mutex);
}