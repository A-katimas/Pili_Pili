/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 17:26:47 by jtardieu          #+#    #+#             */
/*   Updated: 2026/06/26 16:29:00 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "string.h"
#include "codexion.h"

static int print_simulation_info(t_sim *sim);


int	main(int ac, char **av)
{
	t_used	used_var;
	t_sim	sim;

	used_var = parting(ac, av);
	if (used_var.error == 1)
		return (printf("error no good argument"),1);
	if (!init_simulation(&sim, used_var))
		return (printf("Error: failed to initialize simulation\n"),1);

	print_simulation_info(&sim);
	cleanup_simulation(&sim);
	return (0);
}
static int print_simulation_info(t_sim *sim)
{
	printf("Simulation Info:\n");
	printf("  - Coders: %d\n", sim->params.number_of_coders);
	printf("  - Dongles: %d\n", sim->params.number_of_coders);
	printf("  - Scheduler: %s\n", sim->params.scheduler);
	printf("  - Start time: %lld ms\n", sim->start_time);
	return (1);
}
