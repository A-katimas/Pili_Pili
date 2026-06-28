/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 22:43:47 by jtardieu          #+#    #+#             */
/*   Updated: 2026/06/28 23:04:38 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// Ajouter une demande à la queue
void	add_to_queue(t_dongle *dongle, int coder_id, long long arrival_time, long long deadline)
{
	// Redimensionner si nécessaire
	if (dongle->queue_size >= dongle->queue_capacity)
	{
		dongle->queue_capacity *= 2;
		dongle->queue = realloc(dongle->queue,
		                        sizeof(t_request) * dongle->queue_capacity);
	}

	// Ajouter à la fin
	dongle->queue[dongle->queue_size].coder_id = coder_id;
	dongle->queue[dongle->queue_size].arrival_time = arrival_time;
	dongle->queue[dongle->queue_size].deadline = deadline;
	dongle->queue_size++;
}

// Obtenir le PROCHAIN coder selon le scheduler
int	get_next_coder_fifo(t_dongle *dongle)
{
	int	coder_id;

	if (dongle->queue_size == 0)
		return (-1);

	// FIFO : prendre le premier
	coder_id = dongle->queue[0].coder_id;

	// Supprimer de la queue
	for (int i = 0; i < dongle->queue_size - 1; i++)
		dongle->queue[i] = dongle->queue[i + 1];
	dongle->queue_size--;

	return (coder_id);
}

// EDF : obtenir le coder avec la deadline la plus proche
int	get_next_coder_edf(t_dongle *dongle)
{
	int		best_index;
	int		i;
	int		coder_id;

	if (dongle->queue_size == 0)
		return (-1);

	// Trouver celui avec la deadline la plus proche
	best_index = 0;
	i = 1;
	while (i < dongle->queue_size)
	{
		if (dongle->queue[i].deadline < dongle->queue[best_index].deadline)
			best_index = i;
		i++;
	}

	coder_id = dongle->queue[best_index].coder_id;

	// Supprimer de la queue
	for (int j = best_index; j < dongle->queue_size - 1; j++)
		dongle->queue[j] = dongle->queue[j + 1];
	dongle->queue_size--;

	return (coder_id);
}

// Obtenir le prochain selon le scheduler

int	get_next_coder(t_dongle *dongle, const char *scheduler)
{
	int	result;

	if (strcmp(scheduler, "fifo") == 0)
		result = get_next_coder_fifo(dongle);
	else if (strcmp(scheduler, "edf") == 0)
		result = get_next_coder_edf(dongle);
	else
		result = -1;

	return (result);
}