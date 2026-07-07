/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:39:37 by jtardieu          #+#    #+#             */
/*   Updated: 2026/07/07 13:59:11 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// Vérifier si TOUS les coders ont compilé assez
static int	all_coders_done(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->params.number_of_coders)
	{
		if (sim->coders[i].compile_count
			< sim->params.number_of_compiles_required)
			return (0);
		i++;
	}
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
			sim->simulation_active = 0;
			break ;
		}
		if (all_coders_done(sim))
		{
			sim->simulation_active = 0;
			break ;
		}
		usleep(10000);
	}
	return (NULL);
}
