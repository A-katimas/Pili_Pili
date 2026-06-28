/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 23:00:12 by jtardieu          #+#    #+#             */
/*   Updated: 2026/06/28 23:47:56 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_queue_status(t_sim *sim, t_dongle *dongle, int coder_id)
{
	long long	current_time;
	int			i;

	current_time = get_current_time_ms() - sim->start_time;
	pthread_mutex_lock(&sim->log_mutex);
	printf("[DEBUG] Coder %d @ %lld ms - Queue dongle %d: ",
		coder_id, current_time, dongle->id);
	if (dongle->queue_size == 0)
	{
		printf("EMPTY\n");
	}
	else
	{
		i = 0;
		while (i < dongle->queue_size)
		{
			printf("C%d(deadline:%lld) ",
				dongle->queue[i].coder_id,
				dongle->queue[i].deadline);
			i++;
		}
		printf("\n");
	}
	pthread_mutex_unlock(&sim->log_mutex);
}

void	print_scheduler_choice(t_sim *sim, int dongle_id, int coder_chosen)
{
	long long	current_time;

	current_time = get_current_time_ms() - sim->start_time;
	pthread_mutex_lock(&sim->log_mutex);
	printf("[SCHED] %lld ms - Dongle %d gave to Coder %d (%s)\n",
		current_time, dongle_id, coder_chosen, sim->params.scheduler);
	pthread_mutex_unlock(&sim->log_mutex);
}
