/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:54:08 by jtardieu          #+#    #+#             */
/*   Updated: 2026/07/07 11:10:32 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	compile_phase(t_sim *sim, t_coder *coder)
{
	t_dongle	*first_dongle;
	t_dongle	*second_dongle;
	t_dongle	*tmp;

	first_dongle = get_left_dongle(sim, coder->id);
	second_dongle = get_right_dongle(sim, coder->id);
	if (first_dongle->id > second_dongle->id)
	{
		tmp = first_dongle;
		first_dongle = second_dongle;
		second_dongle = tmp;
	}
	take_dongle(sim, first_dongle, coder->id);
	take_dongle(sim, second_dongle, coder->id);
	log_is_compiling(sim, coder->id);
	coder->last_compile_start = get_current_time_ms() - sim->start_time;
	coder->compile_count++;
	usleep(sim->params.time_to_compile * 1000);
	release_dongle(sim, first_dongle);
	release_dongle(sim, second_dongle);
}

static void	debug_phase(t_sim *sim, t_coder *coder)
{
	log_is_debugging(sim, coder->id);
	usleep(sim->params.time_to_debug * 1000);
}

static void	refactor_phase(t_sim *sim, t_coder *coder)
{
	log_is_refactoring(sim, coder->id);
	usleep(sim->params.time_to_refactor * 1000);
}

static int	has_burned_out(t_sim *sim, t_coder *coder)
{
	long long	current_time;
	long long	time_since_last_compile;

	current_time = get_current_time_ms() - sim->start_time;
	time_since_last_compile = current_time - coder->last_compile_start;
	if (time_since_last_compile > sim->params.time_to_burnout)
	{
		coder->burned_out = 1;
		return (1);
	}
	return (0);
}

void	*coder_routine(void *arg)
{
	t_thread_args	*args;
	t_coder			*coder;
	t_sim			*sim;

	args = (t_thread_args *)arg;
	coder = args->coder;
	sim = args->sim;
	while (sim->simulation_active && !coder->burned_out)
	{
		if (has_burned_out(sim, coder))
		{
			log_burned_out(sim, coder->id);
			break ;
		}
		if (coder->compile_count >= sim->params.number_of_compiles_required)
			break ;
		compile_phase(sim, coder);
		debug_phase(sim, coder);
		refactor_phase(sim, coder);
	}
	if (args)
		free(args);
	return (NULL);
}
