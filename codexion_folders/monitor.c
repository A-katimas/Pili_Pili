/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:39:37 by jtardieu          #+#    #+#             */
/*   Updated: 2026/07/08 15:23:12 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// Vérifier si TOUS les coders ont compilé assez
static int	all_coders_done(t_sim *sim)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&sim->state_mutex);
	while (i < sim->params.number_of_coders)
	{
		if (sim->coders[i].compile_count
			< sim->params.number_of_compiles_required)
		{
			pthread_mutex_unlock(&sim->state_mutex);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&sim->state_mutex);
	return (1);
}

// Vérifier si QUELQU'UN a brûlé
static int	someone_burned_out(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->params.number_of_coders)
	{
		if (sim->coders[i].burned_out)
			return (1);
		i++;
	}
	return (0);
}

// Thread monitor
void	*monitor_routine(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	while (sim->simulation_active)
	{
		if (someone_burned_out(sim))
		{
			pthread_mutex_lock (&sim->state_mutex);
			sim->simulation_active = 0;
			pthread_mutex_unlock (&sim->state_mutex);
			break ;
		}
		if (all_coders_done(sim))
		{
			pthread_mutex_lock (&sim->state_mutex);
			sim->simulation_active = 0;
			pthread_mutex_unlock (&sim->state_mutex);
			break ;
		}
		usleep(10000);
	}
	return (NULL);
}
