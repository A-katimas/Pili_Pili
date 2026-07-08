/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:54:08 by jtardieu          #+#    #+#             */
/*   Updated: 2026/07/09 00:10:16 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	compile_phase(t_sim *sim, t_coder *coder)
{
	t_dongle	*first_dongle;
	t_dongle	*second_dongle;

	first_dongle = get_left_dongle(sim, coder->id);
	second_dongle = get_right_dongle(sim, coder->id);
	is_dongel_good(first_dongle, second_dongle, coder, sim);
	take_dongle(sim, first_dongle, coder->id);
	take_dongle(sim, second_dongle, coder->id);
	if (is_burn(sim, coder))
		return (release_dongle(sim, first_dongle),
			release_dongle(sim, second_dongle), 1);
	log_message(sim, coder->id, "is compiling");
	coder->last_compile_start = get_current_time_ms() - sim->start_time;
	pthread_mutex_lock (&sim->state_mutex);
	coder->compile_count++;
	pthread_mutex_unlock (&sim->state_mutex);
	usleep(sim->params.time_to_compile * 1000);
	return (release_dongle(sim, first_dongle),
		release_dongle(sim, second_dongle), 0);
}

static int	debug_phase(t_sim *sim, t_coder *coder)
{
	log_message(sim, coder->id, "is debugging");
	usleep(sim->params.time_to_debug * 1000);
	return (0);
}

static int	refactor_phase(t_sim *sim, t_coder *coder)
{
	log_message(sim, coder->id, "is refactoring");
	usleep(sim->params.time_to_refactor * 1000);
	return (0);
}

int	has_burned_out(t_sim *sim, t_coder *coder)
{
	long long	current_time;
	long long	time_since_last_compile;

	current_time = get_current_time_ms() - sim->start_time;
	time_since_last_compile = current_time - coder->last_compile_start;
	if (time_since_last_compile >= sim->params.time_to_burnout)
	{
		coder->burned_out = 1;
		log_message(sim, coder->id, "burned out");
		sim->burnout = 1;
		return (1);
	}
	else if (sim->burnout)
		return (2);
	return (0);
}

int	used_coder_routine(t_coder	*coder, t_sim *sim)
{
	pthread_mutex_lock (&sim->state_mutex);
	while (sim->simulation_active && !coder->burned_out)
	{
		pthread_mutex_unlock (&sim->state_mutex);
		if (is_burn(sim, coder))
			break ;
		if (coder->compile_count >= sim->params.number_of_compiles_required)
			break ;
		if (is_burn(sim, coder) || compile_phase(sim, coder))
			break ;
		if (is_burn(sim, coder) || debug_phase(sim, coder))
			break ;
		if (is_burn(sim, coder) || refactor_phase(sim, coder))
			break ;
		pthread_mutex_lock (&sim->state_mutex);
	}
	pthread_mutex_unlock (&sim->state_mutex);
	return (0);
}
