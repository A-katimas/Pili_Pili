/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 17:26:47 by jtardieu          #+#    #+#             */
/*   Updated: 2026/06/30 13:48:15 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "string.h"
#include "codexion.h"

int	main(int ac, char **av)
{
	t_used	used_var;
	t_sim	sim;

	used_var = parting(ac, av);
	if (used_var.error == 1)
		return (printf("error no good argument"), 1);
	if (!init_simulation(&sim, used_var))
		return (printf("Error: failed to initialize simulation\n"), 1);
	printf("✓ Simulation initialized !\n\n");
	if (!create_coder_threads(&sim))
		return (cleanup_simulation(&sim), 1);
	wait_all_threads(&sim);
	wait_monitor_thread(&sim);
	printf("\n✓ Simulation finished !\n");
	cleanup_simulation(&sim);
	return (0);
}
