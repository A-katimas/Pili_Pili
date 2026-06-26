/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 16:59:03 by jtardieu          #+#    #+#             */
/*   Updated: 2026/06/26 16:59:04 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	init_dongle(t_dongle *dongle, int id)
{
	dongle->id = id;
	dongle->available = 1;
	dongle->cooldown_end_time = 0;
	pthread_mutex_init(&dongle->mutex, NULL);
}

static void	init_coder(t_coder *coder, int id)
{
	coder->id = id;
	coder->last_compile_start = 0;
	coder->compile_count = 0;
	coder->burned_out = 0;
	coder->thread = 0;
}

static int	init_dongles(t_sim *sim)
{
	int	i;
	int	nb_dongles;

	nb_dongles = sim->params.number_of_coders;
	if (nb_dongles == 1)
		nb_dongles = 1;
	else
		nb_dongles = sim->params.number_of_coders;

	sim->dongles = malloc(sizeof(t_dongle) * nb_dongles);
	if (!sim->dongles)
		return (printf("Error: malloc failed for dongles\n"), 0);

	i = 0;
	while (i < nb_dongles)
	{
		init_dongle(&sim->dongles[i], i);
		i++;
	}
	return (1);
}

static int	init_coders(t_sim *sim)
{
	int	i;

	sim->coders = malloc(sizeof(t_coder) * sim->params.number_of_coders);
	if (!sim->coders)
		return (printf("Error: malloc failed for coders\n"), 0);

	i = 0;
	while (i < sim->params.number_of_coders)
	{
		init_coder(&sim->coders[i], i + 1);
		i++;
	}
	return (1);
}

int	init_simulation(t_sim *sim, t_used params)
{
	sim->params = params;
	sim->start_time = get_current_time_ms();
	sim->simulation_active = 1;
    sim->coders = NULL;
    sim->dongles = NULL;

    if (pthread_mutex_init(&sim->log_mutex, NULL) != 0)
		return (printf("Error: pthread_mutex_init failed\n"), 0);

	if (!init_coders(sim))
		return (pthread_mutex_destroy(&sim->log_mutex),0);

	if (!init_dongles(sim))
		return (pthread_mutex_destroy(&sim->log_mutex),0);

	return (1);
}

