/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 22:31:15 by jtardieu          #+#    #+#             */
/*   Updated: 2026/07/08 15:15:33 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <time.h>

long long	get_current_time_ms(void)
{
	struct timeval	tv;

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
		i = 0;
		while (i < nb_dongles)
		{
			pthread_mutex_destroy(&sim->dongles[i].mutex);
			pthread_cond_destroy(&sim->dongles[i].cond);
			free(sim->dongles[i].queue);
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

	if (sim->burnout)
	{
		return ;
	}
	elapsed_time = get_current_time_ms() - sim->start_time;
	pthread_mutex_lock(&sim->log_mutex);
	if (!sim->burnout)
		printf("%lld %d %s\n", elapsed_time, coder_id, action);
	pthread_mutex_unlock(&sim->log_mutex);
}

long long	get_coder_deadline(t_sim *sim, int coder_id)
{
	return (sim->coders[coder_id - 1].last_compile_start
		+ sim->params.time_to_burnout);
}

// Vérifier si dongle est disponible
int	is_dongle_available(t_dongle *dongle, long long current_time)
{
	return (dongle->cooldown_end_time <= current_time && dongle->available);
}
