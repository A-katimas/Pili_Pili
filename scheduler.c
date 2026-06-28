/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 22:43:47 by jtardieu          #+#    #+#             */
/*   Updated: 2026/06/28 23:40:10 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	add_to_queue(t_dongle *dongle, int coder_id,
	long long arrival_time, long long deadline)
{
	if (dongle->queue_size >= dongle->queue_capacity)
	{
		dongle->queue_capacity *= 2;
		dongle->queue = realloc(dongle->queue,
				sizeof(t_request) * dongle->queue_capacity);
	}
	dongle->queue[dongle->queue_size].coder_id = coder_id;
	dongle->queue[dongle->queue_size].arrival_time = arrival_time;
	dongle->queue[dongle->queue_size].deadline = deadline;
	dongle->queue_size++;
}

int	get_next_coder_fifo(t_dongle *dongle)
{
	int	coder_id;
	int i;

	if (dongle->queue_size == 0)
		return (-1);
	coder_id = dongle->queue[0].coder_id;
	i = 0;
	while (i < dongle->queue_size - 1)
	{
		dongle->queue[i] = dongle->queue[i + 1];
		i++;
	}
	dongle->queue_size--;
	return (coder_id);
}

int	get_next_coder_edf(t_dongle *dongle)
{
	int		best_index;
	int		i;
	int		coder_id;
	int		j;

	if (dongle->queue_size == 0)
		return (-1);
	best_index = 0;
	i = 1;
	while (i < dongle->queue_size)
	{
		if (dongle->queue[i].deadline < dongle->queue[best_index].deadline)
			best_index = i;
		i++;
	}
	coder_id = dongle->queue[best_index].coder_id;
	j = best_index;
	while (j < dongle->queue_size - 1)
	{
		dongle->queue[j] = dongle->queue[j + 1];
		j++;
	}
	dongle->queue_size--;
	return (coder_id);
}

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
