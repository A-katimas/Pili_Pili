/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 23:40:26 by jtardieu          #+#    #+#             */
/*   Updated: 2026/07/07 13:59:54 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// Créer tous les threads des coders
int	create_coder_threads(t_sim *sim)
{
	int				i;
	t_thread_args	*args;

	i = 0;
	while (i < sim->params.number_of_coders)
	{
		args = malloc(sizeof(t_thread_args));
		if (!args)
			return (printf("Error: malloc failed for thread args\n"), 0);
		args->sim = sim;
		args->coder = &sim->coders[i];
		if (pthread_create(&sim->coders[i].thread, NULL,
				coder_routine, args) != 0)
		{
			printf("Error: pthread_create failed for coder %d\n", i + 1);
			free(args);
			return (0);
		}
		i++;
	}
	return (1);
}

// Attendre que tous les threads se terminent
void	wait_all_threads(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->params.number_of_coders)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
}

// Créer le thread monitor
int	create_monitor_thread(t_sim *sim)
{
	if (pthread_create(&sim->monitor_thread, NULL, monitor_routine, sim) != 0)
		return (printf("Error: pthread_create failed\n"), 0);
	return (1);
}

// Attendre le monitor
void	wait_monitor_thread(t_sim *sim)
{
	pthread_join(sim->monitor_thread, NULL);
}
