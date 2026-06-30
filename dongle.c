/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:56:14 by jtardieu          #+#    #+#             */
/*   Updated: 2026/06/30 14:03:22 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//print_queue_status(sim, dongle, coder_id); // ligne 27

//int	take_dongle(t_sim *sim, t_dongle *dongle, int coder_id)
//{
//	long long			current_time;
//	long long			deadline;
//	struct timespec		timeout;
//	int					next_coder;

//	pthread_mutex_lock(&dongle->mutex);
//	current_time = get_current_time_ms() - sim->start_time;
//	deadline = sim->coders[coder_id - 1].last_compile_start
//		+ sim->params.time_to_burnout;
//	add_to_queue(dongle, coder_id, current_time, deadline);
//	while (1)
//	{
//		current_time = get_current_time_ms() - sim->start_time;
//		if (dongle->cooldown_end_time <= current_time && dongle->available)
//		{
//			next_coder = get_next_coder(dongle, sim->params.scheduler);
//			if (next_coder == coder_id)
//			{
//				dongle->available = 0;
//				log_taken_dongle(sim, coder_id);
//				pthread_mutex_unlock(&dongle->mutex);
//				return (1);
//			}
//			else if (next_coder != -1)
//			{
//				deadline = sim->coders[next_coder - 1].last_compile_start
//					+ sim->params.time_to_burnout;
//				add_to_queue(dongle, next_coder, current_time, deadline);
//			}
//		}
//		timeout.tv_sec = 0;
//		timeout.tv_nsec = 10000000;
//		pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &timeout);
//	}
//	return (0);
//}

int	take_dongle(t_sim *sim, t_dongle *dongle, int coder_id)
{
	long long		current_time;
	struct timespec	timeout;

	pthread_mutex_lock(&dongle->mutex);
	current_time = get_current_time_ms() - sim->start_time;
	add_to_queue(dongle, coder_id, current_time,
		get_coder_deadline(sim, coder_id));
	while (1)
	{
		current_time = get_current_time_ms() - sim->start_time;
		if (is_dongle_available(dongle, current_time))
		{
			if (handle_dongle_availability(sim, dongle, coder_id, current_time))
			{
				pthread_mutex_unlock(&dongle->mutex);
				return (1);
			}
		}
		timeout.tv_sec = 0;
		timeout.tv_nsec = 10000000;
		pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &timeout);
	}
	return (0);
}

void	release_dongle(t_sim *sim, t_dongle *dongle)
{
	long long	current_time;

	pthread_mutex_lock(&dongle->mutex);
	current_time = get_current_time_ms() - sim->start_time;
	dongle->cooldown_end_time = current_time + sim->params.dongle_cooldown;
	dongle->available = 1;
	pthread_cond_signal(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}

t_dongle	*get_left_dongle(t_sim *sim, int coder_id)
{
	int	dongle_index;

	if (sim->params.number_of_coders == 1)
		dongle_index = 0;
	else
		dongle_index = coder_id - 1;
	return (&sim->dongles[dongle_index]);
}

t_dongle	*get_right_dongle(t_sim *sim, int coder_id)
{
	int	dongle_index;

	dongle_index = coder_id % sim->params.number_of_coders;
	return (&sim->dongles[dongle_index]);
}

int	handle_dongle_availability(t_sim *sim, t_dongle *dongle,
									int coder_id, long long current_time)
{
	int	next_coder;

	next_coder = get_next_coder(dongle, sim->params.scheduler);
	if (next_coder == coder_id)
	{
		dongle->available = 0;
		log_taken_dongle(sim, coder_id);
		return (1);
	}
	else if (next_coder != -1)
		add_to_queue(dongle, next_coder, current_time,
			get_coder_deadline(sim, next_coder));
	return (0);
}
