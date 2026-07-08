/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burnsecu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 15:31:33 by jtardieu          #+#    #+#             */
/*   Updated: 2026/07/08 16:10:06 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_burn(t_sim *sim, t_coder *coder)
{
	const int	res = has_burned_out(sim, coder);

	if (res == 1)
		return (1);
	else if (res == 2)
		return (1);
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
	coder->last_compile_start = get_current_time_ms();
	used_coder_routine(coder, sim);

	if (args)
		free(args);
	return (NULL);
}
